#pragma once
#include "TutorialGame.h"

namespace NCL {
	namespace CSC8503 {
		class GameServer;
		class GameClient;
		class NetworkPlayer;

		class NetworkedGame : public TutorialGame, public PacketReceiver {
		public:
			NetworkedGame();
			~NetworkedGame();

			void StartAsServer();
			void StartAsClient(char a, char b, char c, char d);

			void UpdateGame(float dt) override;


			void StartLevel();

			void ReceivePacket(int type, GamePacket* payload, int source) override;
			void InsertPlayer(int id, Player* p);
			void RemovePlayer(int ID, Player* p);

			void OnPlayerCollision(NetworkPlayer* a, NetworkPlayer* b);

			std::map<int, GameObject*> GetServerPlayers() { return serverPlayers; };
			std::map<int, GameObject*>::const_iterator GetServerPlayersIterator() const { return serverPlayers.begin(); };
			virtual void UpdateNetworkPostion(GameObject* obj) override;

		protected:
			void UpdateAsServer(float dt);
			void UpdateAsClient(float dt);

			void BroadcastSnapshot(bool deltaFrame);
			void UpdateMinimumState();
			std::map<int, int> stateIDs;

			void SpawnPlayer();

			GameServer* thisServer;
			GameClient* thisClient;
			float timeToNextPacket;
			int packetsToSnapshot;

			int port;
			
			std::vector<NetworkObject*> networkObjects;

			std::map<int, GameObject*> serverPlayers;
			GameObject* localPlayer;
		};
	}
}

