#include "GameServer.h"
#include "GameWorld.h"
#include <iostream>

using namespace NCL;
using namespace CSC8503;

GameServer::GameServer(int onPort, int maxClients)	{
	port		= onPort;
	clientMax	= maxClients;
	clientCount = 0;
	netHandle	= nullptr;
	//threadAlive = false;
	HasSecondPlayer = false;
	log = std::unique_ptr<Logger>(new Logger("Game Server"));

	Initialise();
}

GameServer::~GameServer()	{
	Shutdown();
}

void GameServer::Shutdown() {
	SendGlobalPacket(BasicNetworkMessages::Shutdown);

	//threadAlive = false;
	//updateThread.join();

	enet_host_destroy(netHandle);
	netHandle = nullptr;
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
	//threadAlive		= true;
	//updateThread	= std::thread(&GameServer::ThreadedUpdate, this);

	return true;
}

bool GameServer::SendGlobalPacket(int msgID) {
	GamePacket packet;
	packet.type = msgID;

	return SendGlobalPacket(packet);
}

bool GameServer::SendGlobalPacket(GamePacket& packet) {
	ENetPacket* dataPacket = enet_packet_create(&packet, packet.GetTotalSize(), 0);
	enet_host_broadcast(netHandle, 0, dataPacket);
	return true;
}

bool GameServer::SendPacketToPeer(GamePacket& packet, int id) {
	ENetPacket* dataPacket = enet_packet_create(&packet, packet.GetTotalSize(), 0);

	std::map<int, ENetPeer*>::iterator it;
	for (it = players.begin(); it != players.end(); it++) {
		if (id == it->first)
			enet_peer_send(it->second, 0, dataPacket);
	}
	
	return true;
}

void GameServer::UpdateServer() {
	if (!netHandle) {
		return;
	}

	ENetEvent event;
	while (enet_host_service(netHandle, &event, 0) > 0)	{
		int type	= event.type;
		ENetPeer* p = event.peer;

		int peer = p->incomingPeerID;

		if (type == ENetEventType::ENET_EVENT_TYPE_CONNECT) {
			log->info("Server: New client connected");
			NewPlayerPacket player(peer);
			SendGlobalPacket(player);

			players.insert(std::pair<int, ENetPeer*>(peer, p));				
		}
		else if (type == ENetEventType::ENET_EVENT_TYPE_DISCONNECT) {
			log->info("Server: A client has disconnected");
			PlayerDisconnectPacket player(peer);
			SendGlobalPacket(player);

			players.erase(players.begin(), players.find(p->incomingPeerID));
				
		}
		else if (type == ENetEventType::ENET_EVENT_TYPE_RECEIVE) {
			GamePacket* packet = (GamePacket*)event.packet->data;
			ProcessPacket(packet, peer);
		}
		enet_packet_destroy(event.packet);
	}
}

//void GameServer::ThreadedUpdate() {
//	while (threadAlive) {
//		UpdateServer();
//	}
//}

//Second networking tutorial stuff

void GameServer::SetGameWorld(GameWorld &g) {
	gameWorld = &g;
}