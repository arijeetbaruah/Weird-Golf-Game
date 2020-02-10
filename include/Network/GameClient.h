#pragma once

#include <enet/enet.h>
#include"./NetworkBase.h"
#include "./Logger/Logger.h"

class GameClient : public NetworkBase {
	ENetHost* client;
	Logger* log;

	ENetPeer* netPeer;
public:
	GameClient();
	~GameClient();

	bool Connect(uint8_t a, uint8_t b, uint8_t c, uint8_t d, int portNum);

	void UpdateClient();

	void SendPacket(GamePacket& payload);
};
