#include "./Network/NetworkBase.h"

NetworkBase::NetworkBase() {
	netHandle = nullptr;
}

NetworkBase::~NetworkBase() {
	if (netHandle) {
		enet_host_destroy(netHandle);
	}
}

int NetworkBase::Initialise() {
	return enet_initialize();
}

void NetworkBase::Destroy() {
	enet_deinitialize();
}

bool NetworkBase::ProcessPacket(GamePacket* packet, int peerID) {
	PacketHandlerIterator firstHandler;
	PacketHandlerIterator lastHandler;

	bool canHandle = GetPacketHandlers(packet->type, firstHandler, lastHandler);

	if (canHandle) {
		for (auto i = firstHandler; i != lastHandler; ++i) {
			i->second->ReceivePacket(packet->type, packet, peerID);
		}
		return true;
	}
	//std::cout << __FUNCTION__ << " no handler for packet type " << packet->type << std::endl;
	return false;
}

TestPacketReceiver::TestPacketReceiver(std::string name) {
	this->name = name;
	log = new Logger("Receiver " + name);
}

TestPacketReceiver::~TestPacketReceiver() {
	delete log;
}

void TestPacketReceiver::ReceivePacket(int type, GamePacket* payload, int source) {
	if (type == String_Message) {
		StringPacket* realPacket = (StringPacket*)payload;
		std::string msg = realPacket->GetStringFromData();
		log->info("{} received message : {}", name, msg);
	}
}

