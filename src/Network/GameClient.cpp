#include "./Network/GameClient.h"

GameClient::GameClient() {
	log = new Logger("client");

	client = enet_host_create(NULL /* create a client host */,
		1 /* only allow 1 outgoing connection */,
		2 /* allow up 2 channels to be used, 0 and 1 */,
		0 /* assume any amount of incoming bandwidth */,
		0 /* assume any amount of outgoing bandwidth */);

	if (client == NULL)
	{
		log->error("An error occurred while trying to create an ENet client host.\n");
		exit(EXIT_FAILURE);
		return;
	}
}

GameClient::~GameClient() {
	enet_host_destroy(client);
	delete log;
}

bool GameClient::Connect(uint8_t a, uint8_t b, uint8_t c, uint8_t d, int portNum) {
	ENetAddress address;
	address.port = portNum;

	address.host = (d << 24) | (c << 16) | (b << 8) | (a);

	netPeer = enet_host_connect(client, &address, 2, 0);

	return netPeer != nullptr;
}


void GameClient::UpdateClient() {
	if (client == nullptr)
	{
		return;
	}
	//Handle all incoming packets & send any packets awaiting dispatch
	ENetEvent event;
	while (enet_host_service(client, &event, 0) > 0)
	{
		if (event.type == ENET_EVENT_TYPE_CONNECT) {
			log->info("Client: Connected to server!");
		}
		else if (event.type == ENET_EVENT_TYPE_RECEIVE) {
			log->info("Client: Packet recieved...");
			GamePacket* packet = (GamePacket*)event.packet->data;
			ProcessPacket(packet);
		}
		enet_packet_destroy(event.packet);
	}
}

void GameClient::SendPacket(GamePacket& payload) {
	ENetPacket* dataPacket = enet_packet_create(&payload, payload.GetTotalSize(), 0);

	int test = enet_peer_send(netPeer, 0, dataPacket);
}
