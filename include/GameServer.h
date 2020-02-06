#pragma once

#include <enet/enet.h>
#include"./NetworkBase.h"
#include "Logger.h"

class GameServer : public NetworkBase {
public:
	GameServer(int onPort, int maxClients);
	~GameServer();

	bool Initialise();
	void Shutdown();

	void UpdateServer();

	bool SendGlobalPacket(GamePacket& packet);

protected:
	int			port;
	int			clientMax;
	int			clientCount;
	Logger*		log;


	int incomingDataRate;
	int outgoingDataRate;
};

