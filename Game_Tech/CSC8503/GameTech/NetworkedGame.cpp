#include "NetworkedGame.h"
#include "NetworkPlayer.h"
#include "../CSC8503Common/GameServer.h"
#include "../CSC8503Common/GameClient.h"
#include "../../Plugins/Logger/Logger.h"
#include "../CSC8503Common/cubeDebuff.h"
#include <memory>

#define COLLISION_MSG 30

class PlayerPacketReceiver : public PacketReceiver {
public:
	PlayerPacketReceiver(GameWorld& w, NetworkedGame* g) : world(w), game(g){
		log = std::unique_ptr<Logger>(new Logger("Player Packet"));
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
				log->info("({}, {}, {})", packet.position.x, packet.position.y, packet.position.z);
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
	std::unique_ptr<Logger> log;
};

class NewPlayerPacketReceiver : public PacketReceiver {
public:
	NewPlayerPacketReceiver(GameWorld& w, NetworkedGame* g) : world(w), game(g) {
		log = std::unique_ptr<Logger>(new Logger("New Player"));
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
			else if (realPacket->playerID == 2) {
				pos = Vector3(0.4, 0.1, -0.9);
			}

			GameObject* b = game->AddSphereObjectToWorld(game->getPlayerMesh(realPacket->playerID), pos, Vector3(1, 1, 1), "player" + realPacket->playerID);
			
			log->info("New Player Connected");
			game->InsertPlayer(realPacket->playerID, b);
		}
	}

	GameWorld& world;
	NetworkedGame* game;
	std::unique_ptr<Logger> log;
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
			} else if (realPacket->playerID == 2) {
				pos = Vector3(0.2, 0.1, -0.9);
			} else if (realPacket->playerID == 2) {
				pos = Vector3(0.4, 0.1, -0.9);
			}

			Player* player = game->AddPlayerObjectToWorld(game->getPlayerMesh(realPacket->playerID), pos, Vector3(1, 1, 1), "player" + realPacket->playerID);
			player->isCurrentPlayer = true;
			game->InsertPlayer(realPacket->playerID, player);
		}
	}
	NetworkedGame* game;
};

class PlayerDisconnectPacketReceiver : public PacketReceiver {
public:
	PlayerDisconnectPacketReceiver(GameWorld& w, Player* player, NetworkedGame* g) : world(w), controlledplayer(player), game(g) {
		log = std::unique_ptr<Logger>(new Logger("Player Disconnected"));
	}

	void ReceivePacket(int type, GamePacket* payload, int source) {
		if (type == Player_Disconnected) {
			PlayerDisconnectPacket* realPacket = (PlayerDisconnectPacket*)payload;

			log->info("Player Disconnected");
			game->RemovePlayer(realPacket->playerID, controlledplayer);
		}
	}

	GameWorld& world;
	Player* controlledplayer;
	NetworkedGame* game;
	std::unique_ptr<Logger> log;
};

class SendPacketReceiver : public PacketReceiver {
public:
	SendPacketReceiver(GameWorld& w, NetworkedGame* g) : world(w), game(g) {
		log = std::unique_ptr<Logger>(new Logger("SendPacketReceiver"));
	}

	void ReceivePacket(int type, GamePacket* payload, int source) {
		if (type == Player_Disconnected) {
			SendPacket* realPacket = (SendPacket*)payload;

			log->info("Player Disconnected");
		}
	}

	GameWorld& world;
	NetworkedGame* game;
	std::unique_ptr<Logger> log;
};

class FullPacketReceiver : public PacketReceiver {
public:
	FullPacketReceiver(GameWorld& w, bool p, GameObject* controlled, GameObject* ghost) : world(w), isPlayerServer(p), controlledGoose(controlled), ghostGoose(ghost) {

	}

	void ReceivePacket(int type, GamePacket* payload, int source) {

		if (isPlayerServer)
			return;

		if (type == Full_State) {
			FullPacket* realPacket = (FullPacket*)payload;

			packet = realPacket->fullState;

			if (realPacket->objectID == 1000)
			{
				world.setPlayerOneScore(realPacket->score);
				world.SetPlayerOneTotal(realPacket->totalScore);
				ghostGoose->GetTransform().SetWorldPosition(packet.position);
				ghostGoose->GetTransform().SetLocalOrientation(packet.orientation);
				return;
			}
			else if (realPacket->objectID == 2000)
			{
				world.setPlayerTwoScore(realPacket->score);
				world.SetPlayerTwoTotal(realPacket->totalScore);
				controlledGoose->GetTransform().SetWorldPosition(packet.position);
				//controlledGoose->GetTransform().SetLocalOrientation(packet.orientation);
				return;
			}
			
			std::vector <GameObject*>::const_iterator first;
			std::vector <GameObject*>::const_iterator last;

			world.GetObjectIterators(first, last);

			first += realPacket->objectID;

			std::cout << "Full Packet Received..." << std::endl;

			(*first)->GetRenderObject()->SetColour(packet.colour);
			(*first)->GetTransform().SetWorldPosition(packet.position);
			(*first)->GetTransform().SetLocalOrientation(packet.orientation);
		}
	}
protected:
	GameWorld& world;
	NetworkState packet;
	bool isPlayerServer;
	GameObject* controlledGoose;
	GameObject* ghostGoose;
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
	SendPacketReceiver* serverReceiver = new SendPacketReceiver(*worlds[currentWorld], this);
	thisServer = new GameServer(port, 2);
	thisServer->RegisterPacketHandler(Send_Packet, serverReceiver);
}

void NetworkedGame::StartAsClient(char a, char b, char c, char d)
{
	thisClient = new GameClient();

	PlayerPacketReceiver* serverReceiver = new PlayerPacketReceiver(*worlds[currentWorld], this);
	thisClient->RegisterPacketHandler(Received_State, serverReceiver);

	PlayerIDPacketRecevier* countReceiver = new PlayerIDPacketRecevier(this);
	thisClient->RegisterPacketHandler(Player_ID, &(*countReceiver));

	NewPlayerPacketReceiver* newPlayerPacketReceiver = new NewPlayerPacketReceiver(*worlds[currentWorld], this);
	thisClient->RegisterPacketHandler(Player_Connected, &(*newPlayerPacketReceiver));

	thisClient->Connect(127, 0, 0, 1, port);
}

void NetworkedGame::InsertPlayer(int ID, GameObject* p) {
	otherplayers.push_back(p);
	serverPlayers.insert(std::pair<int, GameObject*>(1, Ball));
}

void NetworkedGame::RemovePlayer(int ID, GameObject* p) {
	std::map<int, GameObject*>::iterator it = serverPlayers.find(1);
	serverPlayers.erase(it);
}

void NetworkedGame::CreateNewPlayer(int id) {
	GameObject* other;
	if (id == 2) {
		other = AddPlayerObjectToWorld(playerTemp1, Vector3(-0.2, 0.1, -0.9), Vector3(1, 1, 1), "player2");
	}
	else if (id == 3) {
		other = AddPlayerObjectToWorld(playerTemp2, Vector3(0.2, 0.1, -0.9) , Vector3(1, 1, 1), "player3");
	}
	else {
		other = AddPlayerObjectToWorld(playerTemp3, Vector3(0.4, 0.1, -0.9) , Vector3(1, 1, 1), "player4");
	}

	InsertPlayer(id, other);
}

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
	if (!thisClient)
		return;
	PlayerPacket packet;
	NetworkState fullState[4];

	for (auto it = serverPlayers.begin(); it != serverPlayers.end(); it++) {
		if (it->second == NULL) {
			continue;
		}
		fullState[it->first].position = it->second->GetTransform().GetWorldPosition();
		fullState[it->first].orientation = it->second->GetTransform().GetLocalOrientation();
		fullState[it->first].playerID = it->first;
		fullState[it->first].valid = true;
		log->info("({}, {}, {})", fullState[it->first].position.x, fullState[it->first].position.y, fullState[it->first].position.z);
	}

	this->thisClient->SendPacket(packet);

}

void NetworkedGame::SpawnPlayer()
{
	float size = 1.0f;
	Player* secondPlayer = new Player(0);

	SphereVolume* volume = new SphereVolume(size);
	secondPlayer->SetBoundingVolume((CollisionVolume*)volume);

	secondPlayer->GetTransform().SetWorldScale(Vector3(size, size, size));
	secondPlayer->GetTransform().SetWorldPosition(Vector3(270, 10, 190));

	secondPlayer->setLayer(2);
	secondPlayer->setLayerMask(0);

	playerTwo = secondPlayer;

	serverPlayers.insert(std::pair<int, Player*>(2, secondPlayer));
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

	ClientPacket newPacket;

	for (int i = 0; i < 6; i++) 
	{
		newPacket.buttonstates[i] = false;
	}

	newPacket.orientation = Ball->GetTransform().GetLocalOrientation();

	if (isServer)
	{
		newPacket.objectID = 1000;

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::W)) {
			newPacket.buttonstates[0] = true;
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::S)) {
			newPacket.buttonstates[1] = true;
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::A)) {
			newPacket.buttonstates[2] = true;

		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::D)) {
			newPacket.buttonstates[3] = true;
		}
	}
	else
	{
		newPacket.objectID = 2000;

		bool* buttonStates = Ball->getButtonStates();

		if (buttonStates[0]) {
			newPacket.buttonstates[0] = true;
		}

		if (buttonStates[1]) {
			newPacket.buttonstates[1] = true;
		}

		if (buttonStates[2]) {
			newPacket.buttonstates[2] = true;

		}

		if (buttonStates[3]) {
			newPacket.buttonstates[3] = true;
		}

		if (buttonStates[4]) {

			newPacket.buttonstates[4] = true;
		}

		if (buttonStates[5]) {
			newPacket.buttonstates[5] = true;
		}
	}
	
	thisClient -> SendPacket(newPacket);
}

void NetworkedGame::BroadcastSnapshot(bool deltaFrame) {
	std::vector < GameObject* >::const_iterator first;
	std::vector < GameObject* >::const_iterator last;
	
	worlds[currentWorld] -> GetObjectIterators(first, last);
	
	for (int j = 0; j < serverPlayers.size(); j++) 
	{
		
		for (auto i = first; i != last; ++i) {
			NetworkObject * o = (*i) -> GetNetworkObject();
			if (!o) {
				continue;
			}
			int playerState = 0; // You �ll need to do this bit !
			GamePacket * newPacket = nullptr;
			if (o -> WritePacket(&newPacket, deltaFrame, playerState)) {
				//thisServer -> SendGlobalPacket(*newPacket); // change ...

				thisServer->SendPacketToPeer(*newPacket, j + 1);
				delete newPacket;
			}
		}
	}
}
