#include "./Network/GameServer.h"

GameServer::GameServer(int onPort, int maxClients) {
	port = onPort;
	clientMax = maxClients;
	clientCount = 0;
	netHandle = nullptr;
	log = new Logger("Server");

	Initialise();
}

GameServer::~GameServer() {
	Shutdown();
	delete log;
}

bool GameServer::Initialise() {
	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = port;

	netHandle = enet_host_create(&address, clientMax, 1, 0, 0);

	if (!netHandle) {

		log->error("{} failed to create network handle!", __FUNCTION__);
		return false;
	}

	return true;
}

void GameServer::Shutdown() {
	enet_host_destroy(netHandle);
	netHandle = nullptr;
}

void GameServer::UpdateServer() {
	if (!netHandle) {
		return;
	}

	ENetEvent event;
	/* Wait up to 1000 milliseconds for an event. */
	while (enet_host_service(netHandle, &event, 1000) > 0)
	{
		int type = event.type;
		ENetPeer* p = event.peer;

		int peer = p->incomingPeerID;

		if (type == ENetEventType::ENET_EVENT_TYPE_CONNECT) {
			log->info("A new client connected from {}:{}.\n",
				event.peer->address.host,
				event.peer->address.port);
			/*NewPlayerPacket player(peer);
			SendGlobalPacket(player);*/
		}
		else if (type == ENetEventType::ENET_EVENT_TYPE_DISCONNECT) {
			log->info("Server: A client has disconnected");
			/*PlayerDisconnectPacket player(peer);
			SendGlobalPacket(player);*/
		}
		else if (type == ENetEventType::ENET_EVENT_TYPE_RECEIVE) {
			GamePacket* packet = (GamePacket*)event.packet->data;
			ProcessPacket(packet, peer);
		}
		enet_packet_destroy(event.packet);
	}
}

bool GameServer::SendGlobalPacket(GamePacket& packet) {
	ENetPacket* dataPacket = enet_packet_create(&packet, packet.GetTotalSize(), 0);
	enet_host_broadcast(netHandle, 0, dataPacket);
	return true;
}
