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

			if (game->getIsServer())
				return;

			PlayerPacket* realPacket = (PlayerPacket*)payload;
			auto serverPlayers = game->GetServerPlayers();

			int playerCount = 0;

			if (realPacket->switchingLevel)
				game->changeLevel();

			for (NetworkState& packet : realPacket->fullState) {
				if (!packet.valid) {
					continue;
				}
				playerCount++;
				serverPlayers[packet.playerID]->GetTransform().SetWorldPosition(packet.position);
				serverPlayers[packet.playerID]->GetTransform().SetLocalOrientation(packet.orientation);

				AddComponent(packet.powerUps, serverPlayers[packet.playerID]);
			}

			game->currentPlayerCount = playerCount;
		}
	}

	void AddComponent(NetworkPowerUps powerUps, GameObject* target) {

		
		if (powerUps == NetworkPowerUps::SQUARE) {
			Player* p = dynamic_cast<Player*>(target);
			target->GetTransform().SetWorldScale(Vector3(0.05, 0.05, 0.05) * p->getSizeScale());
			target->SetRenderObject(new RenderObject(&p->GetTransform(), p->GetCubeMesh(), p->GetRenderObject()->GetDefaultTexture(), p->GetRenderObject()->GetShader()));
			game->setPowerUpName("BOXED IN!");
		}
		else if (powerUps == NetworkPowerUps::SIZE) {
			Player* p = dynamic_cast<Player*>(target);
			if (target->GetTransform().GetLocalScale() == (Vector3(1, 1, 1) * p->getSizeScale()))
			{
				p->GetTransform().SetWorldScale(p->GetTransform().GetLocalScale() * 2);
				//p->setSizeScale(2);
				game->setPowerUpName("BIG BALL!");
			}
		}
		else if (powerUps == NetworkPowerUps::HOMING) {
			game->setPowerUpName("HOMING BALL!");
		}
		else if (powerUps == NetworkPowerUps::SPEED) {
			game->setPowerUpName("SPEED BOOST!");
		}
		else if (powerUps == NetworkPowerUps::DIRECTION) {
			game->setPowerUpName("DIRECTION CHANGE!");
		}
		else if (powerUps == NetworkPowerUps::CURVE) {
			game->setPowerUpName("CURVE BALL!");
		}
		else if (powerUps == NetworkPowerUps::NONE) {
			Player* p = dynamic_cast<Player*>(target);

			if (target->GetRenderObject()->GetMesh() == p->GetCubeMesh())
				target->SetRenderObject(new RenderObject(&p->GetTransform(), p->GetPlayerMesh(), p->GetRenderObject()->GetDefaultTexture(), p->GetRenderObject()->GetShader()));
			else if (target->GetTransform().GetLocalScale() != (Vector3(1, 1, 1) * p->getSizeScale()))
			{
				p->setSizeScale(1);
				target->GetTransform().SetWorldScale(Vector3(1, 1, 1) * p->getSizeScale());
			}
		}
	}

	GameWorld& world;
	NetworkedGame* game;
};

class PlayerDisconnectPacketReceiver : public PacketReceiver {
public:
	PlayerDisconnectPacketReceiver(GameWorld& w, NetworkedGame* g) : world(w), game(g) {
	}

	void ReceivePacket(int type, GamePacket* payload, int source) {
		if (type == Player_Disconnected) {
			PlayerDisconnectPacket* realPacket = (PlayerDisconnectPacket*)payload;

			game->RemovePlayer(realPacket->playerID);
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

			game->currentPlayerCount++;

			Player* b = game->AddSphereObjectToWorld(game->getPlayerMesh(realPacket->playerID), pos, 0, realPacket->playerID, Vector3(1, 1, 1), "player" + realPacket->playerID);

			b->isServer = true;
			
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
			if (game->hasPlayer())
				return;

			PlayerIDPacket* realPacket = (PlayerIDPacket*)payload;

			Vector3 pos;
			if (realPacket->playerID == 0) {
				pos = Vector3(-0.4, 0.1, -0.9);

			} else if (realPacket->playerID == 1) {
				pos = Vector3(-0.2, 0.1, -0.9);
				Player* b = game->AddSphereObjectToWorld(game->getPlayerMesh(0), Vector3(-0.4, 0.1, -0.9), 0, 0, Vector3(1, 1, 1), "player" + 0);
				game->InsertPlayer(0, b);

			} else if (realPacket->playerID == 2) {
				pos = Vector3(0.2, 0.1, -0.9);

				Player* b = game->AddSphereObjectToWorld(game->getPlayerMesh(0), Vector3(-0.4, 0.1, -0.9), 0, 0, Vector3(1, 1, 1), "player" + 0);
				game->InsertPlayer(0, b);

				Player* c = game->AddSphereObjectToWorld(game->getPlayerMesh(1), Vector3(-0.4, 0.1, -0.9), 0, 1, Vector3(1, 1, 1), "player" + 1);
				game->InsertPlayer(1, c);

			} else if (realPacket->playerID == 3) {
				pos = Vector3(0.4, 0.1, -0.9);

				Player* b = game->AddSphereObjectToWorld(game->getPlayerMesh(0), Vector3(-0.4, 0.1, -0.9), 0, 0, Vector3(1, 1, 1), "player" + 0);
				game->InsertPlayer(0, b);

				Player* c = game->AddSphereObjectToWorld(game->getPlayerMesh(1), Vector3(-0.4, 0.1, -0.9), 0, 1, Vector3(1, 1, 1), "player" + 1);
				game->InsertPlayer(1, c);

				Player* d = game->AddSphereObjectToWorld(game->getPlayerMesh(2), Vector3(-0.4, 0.1, -0.9), 0, 2, Vector3(1, 1, 1), "player" + 2);
				game->InsertPlayer(2, d);
			}

			Player* player = game->AddPlayerObjectToWorld(game->getPlayerMesh(realPacket->playerID), pos, 0, realPacket->playerID, Vector3(1, 1, 1), "player" + realPacket->playerID);

			if (realPacket->playerID == 0)
				player->isServer = true;

			player->isCurrentPlayer = true;
			game->InsertPlayer(realPacket->playerID, player);
		}
	}
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
				players[realPacket->playerID]->getComponent<ShotTracker*>("ShotTracker")->addShots();
			}

			PxVec3 temp = PxVec3(realPacket->force.x, realPacket->force.y, realPacket->force.z);
			if (players[realPacket->playerID]->getOffset()) {
				temp = PxVec3(temp.z, temp.y, temp.x);
			}
			players[realPacket->playerID]->getComponent<PhysicsComponent*>("PhysicsComponent")->addForce(temp);
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

class StarRemovedReceiver : public PacketReceiver {
public:
	StarRemovedReceiver(GameWorld& w, NetworkedGame* g) : world(w), game(g) {

	}

	void ReceivePacket(int type, GamePacket* payload, int source) {
		if (type == Star_Removed) {

			if (game->getIsServer())
				return;

			StarRemovedPacket* realPacket = (StarRemovedPacket*)payload;

			for (int i = 0; i < world.starList.size(); i++)
			{
				if (world.starList[i]->GetNetworkObject()->GetID() == realPacket->objectID)
					world.RemoveGameObject(world.starList[i]);
			}
		}
	}
protected:
	GameWorld& world;
	NetworkedGame* game;
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

void NetworkedGame::ResetServerPacketReceivers() 
{
	thisServer->ClearPacketHandlers();

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

	StarRemovedReceiver* StarRemovedPacketReceiver = new StarRemovedReceiver(*worlds[currentWorld], this);
	thisClient->RegisterPacketHandler(Star_Removed, &(*StarRemovedPacketReceiver));

	PlayerDisconnectPacketReceiver* playerDisconnectPacketReceiver = new PlayerDisconnectPacketReceiver(*worlds[currentWorld], this);
	thisClient->RegisterPacketHandler(Player_Disconnected, &(*playerDisconnectPacketReceiver));

	thisClient->Connect(127, 0, 0, 1, port);
}

void NetworkedGame::ResetClientPacketReceivers()
{
	thisClient->ClearPacketHandlers();

	PlayerPacketReceiver* serverReceiver = new PlayerPacketReceiver(*worlds[currentWorld], this);
	thisClient->RegisterPacketHandler(Received_State, &(*serverReceiver));

	PlayerIDPacketRecevier* countReceiver = new PlayerIDPacketRecevier(this);
	thisClient->RegisterPacketHandler(Player_ID, &(*countReceiver));

	NewPlayerPacketReceiver* newPlayerPacketReceiver = new NewPlayerPacketReceiver(*worlds[currentWorld], this);
	thisClient->RegisterPacketHandler(Player_Connected, &(*newPlayerPacketReceiver));

	StarRemovedReceiver* StarRemovedPacketReceiver = new StarRemovedReceiver(*worlds[currentWorld], this);
	thisClient->RegisterPacketHandler(Star_Removed, &(*StarRemovedPacketReceiver));

	PlayerDisconnectPacketReceiver* playerDisconnectPacketReceiver = new PlayerDisconnectPacketReceiver(*worlds[currentWorld], this);
	thisClient->RegisterPacketHandler(Player_Disconnected, &(*playerDisconnectPacketReceiver));

}

void NetworkedGame::InsertPlayer(int ID, GameObject* p) {
	otherplayers.push_back(p);
	serverPlayers.insert(std::pair<int, GameObject*>(ID, p));
}

void NetworkedGame::RemovePlayer(int ID) {

	std::map<int, GameObject*>::iterator it = serverPlayers.find(ID);

	if (it == serverPlayers.end())
		return;
	
	GameObject* p = (*it).second;

	p->RemoveComponent("PhysicsComponent");

	worlds[currentWorld]->RemoveGameObject(p);

	serverPlayers.erase(it);
}

void NetworkedGame::UpdateGame(float dt)
{
	
	TutorialGame::UpdateGame(dt);

	if (switchingLevels)
	{
		if (isServer)
			ResetServerPacketReceivers();

		ResetClientPacketReceivers();

		switchingLevels = false;
	}


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

		if (switchingLevels)
			packet.switchingLevel = true;
		else
			packet.switchingLevel = false;

		switchingLevels = false;

		for (auto it = serverPlayers.begin(); it != serverPlayers.end(); it++) {
			if (it->second == NULL) {
				continue;
			}
			packet.fullState[it->first].position = it->second->GetTransform().GetWorldPosition();
			packet.fullState[it->first].orientation = it->second->GetTransform().GetLocalOrientation();
			packet.fullState[it->first].playerID = it->first;
			packet.fullState[it->first].valid = true;

			Player* p = dynamic_cast<Player*>(it->second);
			packet.fullState[it->first].powerUps = p->getCurrentPowerUp();
		}

		this->thisServer->SendGlobalPacket(packet);

		StarRemovedPacket starPacket;

		for (int i = 0; i < worlds[currentWorld]->starList.size(); i++) {
			if (worlds[currentWorld]->starList[i] != nullptr) {
				continue;
			}

			starPacket.objectID = i + 1000;
			this->thisServer->SendGlobalPacket(starPacket);
		}

	}

	if (thisClient) {
		
	}
}

void NetworkedGame::EndSession()
{
	if (isServer || !Ball)
		return;

	int packetCount = 1000;

	for (int i = 0; i < packetCount; i++)
	{
		PlayerDisconnectPacket packet(Ball->getID());
		thisClient->SendPacket(packet);
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
