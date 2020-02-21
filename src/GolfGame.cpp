#include "GolfGame.h"
#include "./Common/Window.h"

GolfGame::GolfGame() {
	log = std::unique_ptr<Logger>(new Logger("Golf Game"));
	
	port = NetworkBase::GetDefaultPort();

	if (NetworkBase::Initialise() != 0) {
		log->error("An error occurred while initializing ENet.\n");
		errorFlag = EXIT_FAILURE;
		return;
	}

	physxC.spawnBall();
}

GolfGame::~GolfGame() {
	NetworkBase::Destroy();
}

void GolfGame::UpdateGame(float dt) {
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NUM1)) {
		StartAsServer(2);
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NUM2)) {
		StartAsClient(127, 0, 0, 1);
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NUM3)) {
		physxC.spawnBall();
	}
	physxC.stepPhysics(true, dt);
	UpdateNetwork();
}

void GolfGame::UpdateNetwork() {
	if (isServer) {
		this->thisServer->UpdateServer();
	}
	if (isClient) {
		this->thisClient->UpdateClient();
	}
}

void GolfGame::StartAsServer(const int maxPlayer) {
	ServerPacketReceiver serverReceiver("server packet Receiver");
	thisServer = new GameServer(port, maxPlayer);
	thisServer->RegisterPacketHandler(Received_State, &serverReceiver);
	isServer = true;
}

void GolfGame::StartAsClient(char a, char b, char c, char d) {
	thisClient = new GameClient();

	FullPacketReceiver* clientReceiver = new FullPacketReceiver("test");
	thisClient->RegisterPacketHandler(Received_State, &(*clientReceiver));

	thisClient->Connect(127, 0, 0, 1, port);
	isClient = true;
}

void GolfGame::ReceivePacket(int type, GamePacket* payload, int source) {
	this->thisServer->UpdateServer();
}
