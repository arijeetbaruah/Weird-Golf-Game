#pragma once

#include "Logger/Logger.h"
#include "Network/GameServer.h"
#include "Network/GameClient.h"
#include <memory>

class ServerPacketReceiver : public PacketReceiver
{
protected:
	std::string name;
	std::unique_ptr<Logger> log;
public:
	ServerPacketReceiver(std::string name) {
		log = std::unique_ptr<Logger>(new Logger("Server Packet Receiver"));
	}
	~ServerPacketReceiver() {}
	void ReceivePacket(int type, GamePacket* payload, int source) {
		if (type == Received_State) {
			StringPacket* sp = (StringPacket*)payload;
			log->info(sp->GetStringFromData());
		}
	}
};

class FullPacketReceiver : public PacketReceiver
{
protected:
	std::string name;
	std::unique_ptr<Logger> log;
public:
	FullPacketReceiver(std::string name) {
		log = std::unique_ptr<Logger>(new Logger("Full Packet Receiver"));
	}
	~FullPacketReceiver() {}
	void ReceivePacket(int type, GamePacket* payload, int source) {
		if (type == Received_State) {
			StringPacket* sp = (StringPacket*)payload;
			log->info(sp->GetStringFromData());
		}
	}
};


class GolfGame : public PacketReceiver
{
public:
public:
	GolfGame();
	~GolfGame();

	virtual void UpdateGame(float dt);
	void StartAsServer(const int maxPlayer);
	void StartAsClient(char a, char b, char c, char d);

	int hasError() const { return errorFlag; }
protected:
	std::unique_ptr<Logger> log;
	int port;
	int errorFlag = 0;

	void UpdateNetwork();
	void ReceivePacket(int type, GamePacket* payload, int source);

	bool isServer = false;
	bool isClient = false;

	GameServer* thisServer;
	GameClient* thisClient;
};
