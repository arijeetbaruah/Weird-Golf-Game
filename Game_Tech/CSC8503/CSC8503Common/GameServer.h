#pragma once
#include <thread>
#include <atomic>
#include <memory>

#include "NetworkBase.h"
#include "../../Plugins/Logger/Logger.h"

namespace NCL {
	namespace CSC8503 {
		class GameWorld;
		class GameServer : public NetworkBase {
		public:
			GameServer(int onPort, int maxClients);
			~GameServer();

			bool Initialise();
			void Shutdown();

			void SetGameWorld(GameWorld &g);

			//void ThreadedUpdate();

			bool SendGlobalPacket(int msgID);
			bool SendGlobalPacket(GamePacket& packet);
			bool SendPacketToPeer(GamePacket& packet, int ID);

			virtual void UpdateServer();

			bool SecondPlayerEntered() { return HasSecondPlayer; };

		protected:
			int			port;
			int			clientMax;
			int			clientCount;
			GameWorld*	gameWorld;
			std::unique_ptr<Logger> log;

			//std::atomic<bool> threadAlive;

			bool HasSecondPlayer;

			//std::thread updateThread;

			int incomingDataRate;
			int outgoingDataRate;
		};
	}
}
