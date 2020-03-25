#include "NetworkedGame.h"
#include "NetworkPlayer.h"
#include "../CSC8503Common/GameServer.h"
#include "../CSC8503Common/GameClient.h"
#include "../CSC8503Common/ShotTracker.h"
#include "../CSC8503Common/cubeDebuff.h"
#include <memory>
#include <iostream>

#define COLLISION_MSG 30

class PlayerPacketReceiver : public PacketReceiver {
public:
	PlayerPacketReceiver(GameWorld& w, NetworkedGame* g) : world(w), game(g){
	}

	void ReceivePacket(int type, GamePacket* payload, int source) {
		if (type == Received_State) {
			PlayerPacket* realPacket = (PlayerPacket*)payload;
			auto serverPlayers = game->GetServerPlayers();


			for (NetworkState& packet : realPacket->fullState) {
				if (!packet.valid) {
					continue;
				}
				serverPlayers[packet.playerID]->GetTransform().SetWorldPosition(packet.position);
				serverPlayers[packet.playerID]->GetTransform().SetLocalOrientation(packet.orientation);
				AddComponent(packet.powerUps, serverPlayers[packet.playerID]);
			}
		}
	}

	void AddComponent(NetworkPowerUps powerUps, GameObject* target) {
		if (powerUps == NetworkPowerUps::SQUARE) {
			cubeDebuff* cubed = new cubeDebuff(target->GetPlayerMesh(), target->GetCubeMesh());
			target->addComponent(cubed);
		}
	}

	GameWorld& world;
	NetworkedGame* game;
};

class NewPlayerPacketReceiver : public PacketReceiver {
public:
	NewPlayerPacketReceiver(GameWorld& w, NetworkedGame* g) : world(w), game(g) {
	}

	void ReceivePacket(int type, GamePacket* payload, int source) {
		if (type == Player_Connected) {
			NewPlayerPacket* realPacket = (NewPlayerPacket*)payload;

			if (game->GetCurrentPlayer() == NULL) {
				return;
			}
			if (game->GetCurrentPlayer()->getID() == realPacket->playerID) {
				return;
			}

			Vector3 pos;
			if (realPacket->playerID == 0) {
				pos = Vector3(-0.4, 0.1, -0.9);
			}
			else if (realPacket->playerID == 1) {
				pos = Vector3(-0.2, 0.1, -0.9);
			}
			else if (realPacket->playerID == 2) {
				pos = Vector3(0.2, 0.1, -0.9);
			}
			else if (realPacket->playerID == 3) {
				pos = Vector3(0.4, 0.1, -0.9);
			}

			// TODO BOH
			GameObject* b = game->AddSphereObjectToWorld(game->getPlayerMesh(realPacket->playerID), pos, 0, realPacket->playerID, Vector3(1, 1, 1), "player" + realPacket->playerID);
			
			game->InsertPlayer(realPacket->playerID, b);
		}
	}

	GameWorld& world;
	NetworkedGame* game;
};

class PlayerIDPacketRecevier : public PacketReceiver {
public:
	PlayerIDPacketRecevier(NetworkedGame* ng) : game(ng) {}

	void ReceivePacket(int type, GamePacket* payload, int source) {
		if (type == Player_ID) {
			PlayerIDPacket* realPacket = (PlayerIDPacket*)payload;
			//game->InsertPlayer(realPacket->playerID, game->GetCurrentPlayer());

			Vector3 pos;
			if (realPacket->playerID == 0) {
				pos = Vector3(-0.4, 0.1, -0.9);
			} else if (realPacket->playerID == 1) {
				pos = Vector3(-0.2, 0.1, -0.9);
				GameObject* b = game->AddSphereObjectToWorld(game->getPlayerMesh(0), Vector3(-0.4, 0.1, -0.9), 0, 0, Vector3(1, 1, 1), "player" + 0);
				game->InsertPlayer(0, b);
			} else if (realPacket->playerID == 2) {
				pos = Vector3(0.2, 0.1, -0.9);

				GameObject* b = game->AddSphereObjectToWorld(game->getPlayerMesh(0), Vector3(-0.4, 0.1, -0.9), 0, 0, Vector3(1, 1, 1), "player" + 0);
				game->InsertPlayer(0, b);

				GameObject* c = game->AddSphereObjectToWorld(game->getPlayerMesh(1), Vector3(-0.4, 0.1, -0.9), 0, 1, Vector3(1, 1, 1), "player" + 1);
				game->InsertPlayer(1, c);
			} else if (realPacket->playerID == 3) {
				pos = Vector3(0.4, 0.1, -0.9);

				GameObject* b = game->AddSphereObjectToWorld(game->getPlayerMesh(0), Vector3(-0.4, 0.1, -0.9), 0, 0, Vector3(1, 1, 1), "player" + 0);
				game->InsertPlayer(0, b);

				GameObject* c = game->AddSphereObjectToWorld(game->getPlayerMesh(1), Vector3(-0.4, 0.1, -0.9), 0, 1, Vector3(1, 1, 1), "player" + 1);
				game->InsertPlayer(1, c);

				GameObject* d = game->AddSphereObjectToWorld(game->getPlayerMesh(2), Vector3(-0.4, 0.1, -0.9), 0, 2, Vector3(1, 1, 1), "player" + 2);
				game->InsertPlayer(2, d);
			}

			//GameObject* b = game->AddSphereObjectToWorld(game->getPlayerMesh(1), Vector3(-0.4, 0.1, -0.9), 0, 1, Vector3(1, 1, 1), "player" + 1);
			//game->InsertPlayer(1, b);

			Player* player = game->AddPlayerObjectToWorld(game->getPlayerMesh(realPacket->playerID), pos, 0, realPacket->playerID, Vector3(1, 1, 1), "player" + realPacket->playerID); // TODO: BOH
			player->isCurrentPlayer = true;
			game->InsertPlayer(realPacket->playerID, player);
		}
	}
	NetworkedGame* game;
};

class PlayerDisconnectPacketReceiver : public PacketReceiver {
public:
	PlayerDisconnectPacketReceiver(GameWorld& w, Player* player, NetworkedGame* g) : world(w), controlledplayer(player), game(g) {
	}

	void ReceivePacket(int type, GamePacket* payload, int source) {
		if (type == Player_Disconnected) {
			PlayerDisconnectPacket* realPacket = (PlayerDisconnectPacket*)payload;

			game->RemovePlayer(realPacket->playerID, controlledplayer);
		}
	}

	GameWorld& world;
	Player* controlledplayer;
	NetworkedGame* game;
};

class SendPacketReceiver : public PacketReceiver {
public:
	SendPacketReceiver(GameWorld& w, NetworkedGame* g) : world(w), game(g) {
	}

	void ReceivePacket(int type, GamePacket* payload, int source) {
		if (type == Player_Disconnected) {
			SendPacket* realPacket = (SendPacket*)payload;
		}
	}

	GameWorld& world;
	NetworkedGame* game;
};

class FullPacketReceiver : public PacketReceiver {
public:
	FullPacketReceiver(GameWorld& w, NetworkedGame* g) : world(w), game(g) {
	}

	void ReceivePacket(int type, GamePacket* payload, int source) {
		if (type == Full_State) {
			FullPacket* realPacket = (FullPacket*)payload;

			auto players = game->GetServerPlayers();
//#ifdef WIN32
//			Player* p = dynamic_cast<Player*>(players[realPacket->playerID]);
//#else 
//			Player* p = (Player*)(players[realPacket->playerID]);
//#endif

			if (realPacket->force.x > 0 || realPacket->force.y > 0 || realPacket->force.z > 0)
			{
				int i = 0;
			}

			players[realPacket->playerID]->getComponent<PhysicsComponent*>("PhysicsComponent")->addForce(PxVec3(realPacket->force.x, realPacket->force.y, realPacket->force.z));
		}
	}
protected:
	GameWorld& world;
	NetworkedGame* game;
};

class ConnectedPacketReceiver : public PacketReceiver {
public:
	ConnectedPacketReceiver(NetworkedGame& g) : networkedGame(g) {

	}

	void ReceivePacket(int type, GamePacket* payload, int source) {
		if (type == Player_Connected) {
			ClientPacket* realPacket = (ClientPacket*)payload;

			/*if (networkedGame.GetServerPlayers().size() == 1)
				networkedGame.SpawnPlayer();*/
		}
	}
protected:
	NetworkedGame& networkedGame;
};

class CollectableCountReceiver : public PacketReceiver {
public:
	CollectableCountReceiver(GameWorld& w) : world(w) {

	}

	void ReceivePacket(int type, GamePacket* payload, int source) {
		if (type == Collectable_Count) {
			CollectableCountPacket* realPacket = (CollectableCountPacket*)payload;

			world.SetCollectableCount(realPacket->count);
		}
	}
protected:
	GameWorld& world;
};


NetworkedGame::NetworkedGame()
{
	port = NetworkBase::GetDefaultPort();
	//SpawnPlayer();
}

NetworkedGame::~NetworkedGame()
{

}

void NetworkedGame::StartAsServer()
{
	thisServer = new GameServer(port, 4);

	SendPacketReceiver* serverReceiver = new SendPacketReceiver(*worlds[currentWorld], this);
	FullPacketReceiver* fullReceiver = new FullPacketReceiver(*worlds[currentWorld], this);

	thisServer->RegisterPacketHandler(Send_Packet, serverReceiver);
	thisServer->RegisterPacketHandler(Full_State, fullReceiver);
}

void NetworkedGame::StartAsClient(char a, char b, char c, char d)
{
	thisClient = new GameClient();

	PlayerPacketReceiver* serverReceiver = new PlayerPacketReceiver(*worlds[currentWorld], this);
	thisClient->RegisterPacketHandler(Received_State, &(*serverReceiver));

	PlayerIDPacketRecevier* countReceiver = new PlayerIDPacketRecevier(this);
	thisClient->RegisterPacketHandler(Player_ID, &(*countReceiver));

	NewPlayerPacketReceiver* newPlayerPacketReceiver = new NewPlayerPacketReceiver(*worlds[currentWorld], this);
	thisClient->RegisterPacketHandler(Player_Connected, &(*newPlayerPacketReceiver));

	thisClient->Connect(127, 0, 0, 1, port);
}

void NetworkedGame::InsertPlayer(int ID, GameObject* p) {
	otherplayers.push_back(p);
	serverPlayers.insert(std::pair<int, GameObject*>(ID, p));
}

void NetworkedGame::RemovePlayer(int ID, GameObject* p) {
	std::map<int, GameObject*>::iterator it = serverPlayers.find(ID);
	serverPlayers.erase(it);
}

// TODO: BOH
//void NetworkedGame::CreateNewPlayer(int id) {
//	GameObject* other;
//	if (id == 2) {
//		other = AddPlayerObjectToWorld(playerTemp1, Vector3(-0.2, 0.1, -0.9), 0, Vector3(1, 1, 1), "player2");
//	}
//	else if (id == 3) {
//		other = AddPlayerObjectToWorld(playerTemp2, Vector3(0.2, 0.1, -0.9), 0, Vector3(1, 1, 1), "player3");
//	}
//	else {
//		other = AddPlayerObjectToWorld(playerTemp3, Vector3(0.4, 0.1, -0.9), 0, Vector3(1, 1, 1), "player4");
//	}
//
//	InsertPlayer(id, other);
//}

void NetworkedGame::UpdateGame(float dt)
{
	
	TutorialGame::UpdateGame(dt);

	/*if (Ball && serverPlayers.size() == 0)
		serverPlayers.insert(std::pair<int, GameObject*>(1, (GameObject*)Ball));*/

	if (!isNetworkedGame)
		return;

	if (!thisServer && isServer)
		StartAsServer();

	if (!thisClient)
		StartAsClient(' ', ' ', ' ', ' ');

	if (thisServer)
		UpdateAsServer(dt);
	
	UpdateAsClient(dt);
	
}

void NetworkedGame::UpdateNetworkPostion(GameObject* obj) {
	if (thisServer) {
		PlayerPacket packet;

		for (auto it = serverPlayers.begin(); it != serverPlayers.end(); it++) {
			if (it->second == NULL) {
				continue;
			}
			packet.fullState[it->first].position = it->second->GetTransform().GetWorldPosition();
			packet.fullState[it->first].orientation = it->second->GetTransform().GetLocalOrientation();
			packet.fullState[it->first].playerID = it->first;
			packet.fullState[it->first].valid = true;
		}

		this->thisServer->SendGlobalPacket(packet);
	}

	if (thisClient) {
		
	}

}

void NetworkedGame::StartLevel()
{

}

void NetworkedGame::ReceivePacket(int type, GamePacket* payload, int source)
{

}

void NetworkedGame::OnPlayerCollision(NetworkPlayer* a, NetworkPlayer* b)
{

}

void NetworkedGame::UpdateAsServer(float dt)
{
	thisServer->UpdateServer();
	BroadcastSnapshot(false);

	/*CollectableCountPacket* packet = new CollectableCountPacket();
	packet->count = world->GetCollectableCount();*/

	//thisServer->SendPacketToPeer(*packet, 2);
	//delete packet;

}

void NetworkedGame::UpdateAsClient(float dt) {
	thisClient->UpdateClient();

	if (isServer || Ball == NULL)
		return;

	BroadcastSnapshot(false);

}

void NetworkedGame::BroadcastSnapshot(bool deltaFrame) {
	if (Ball == NULL)
		return;
	if (thisClient) {
		FullPacket packet;
		packet.playerID = Ball->getID();
		packet.force = Ball->getForceState();
		Ball->resetForceState();
		thisClient->SendPacket(packet);
	}
}
