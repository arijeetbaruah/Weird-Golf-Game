#pragma once
#pragma comment(lib, "secur32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dmoguids.lib")
#pragma comment(lib, "wmcodecdspuuid.lib")
#pragma comment(lib, "msdmo.lib")
#pragma comment(lib, "Strmiids.lib")
#pragma comment(lib, "Ws2_32.lib")

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <map>
#include <enet/enet.h>
#include <iostream>
#include "./Logger/Logger.h"

enum BasicNetworkMessages {
	None,
	Hello,
	Message,
	String_Message,
	Delta_State,	//1 byte per channel since the last state
	Full_State,		//Full transform etc
	Received_State, //received from a client, informs that its received packet n
	Player_Connected,
	Player_Disconnected,
	Shutdown
};

struct GamePacket {
	short size;
	short type;

	GamePacket() {
		type = BasicNetworkMessages::None;
		size = 0;
	}

	GamePacket(short type) : GamePacket() {
		this->type = type;
	}

	int GetTotalSize() {
		return sizeof(GamePacket) + size;
	}
};

class PacketReceiver {
public:
	virtual void ReceivePacket(int type, GamePacket* payload, int source = -1) = 0;
};


struct StringPacket : public GamePacket {
	char	stringData[256];

	StringPacket(const std::string& message) {
		type = BasicNetworkMessages::String_Message;
		size = (short)message.length();

		memcpy(stringData, message.data(), size);
	};

	std::string GetStringFromData() {
		std::string realString(stringData);
		realString.resize(size);
		return realString;
	}
};

class NetworkBase
{
public:
	NetworkBase();
	~NetworkBase();

	static int Initialise();
	static void Destroy();

	static int GetDefaultPort() { return 1234; }

	void RegisterPacketHandler(int msgID, PacketReceiver* receiver) {
		packetHandlers.insert(std::make_pair(msgID, receiver));
	}
protected:
	ENetHost* netHandle;
	std::multimap<int, PacketReceiver*> packetHandlers;

	typedef std::multimap<int, PacketReceiver*>::const_iterator PacketHandlerIterator;

	bool ProcessPacket(GamePacket* p, int peerID = -1);

	bool GetPacketHandlers(int msgID, PacketHandlerIterator& first, PacketHandlerIterator& last) const {
		auto range = packetHandlers.equal_range(msgID);

		if (range.first == packetHandlers.end()) {
			return false; //no handlers for this message type!
		}
		first = range.first;
		last = range.second;
		return true;
	}
};

class TestPacketReceiver : public PacketReceiver
{
protected:
	std::string name;
	Logger* log;
public:
	TestPacketReceiver(std::string name);
	~TestPacketReceiver();
	void ReceivePacket(int type, GamePacket* payload, int source);
};


