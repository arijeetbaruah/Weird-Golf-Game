// LogTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "./Logger/Logger.h"

#include "./AI/StateMachine.h"
#include "./AI//StateTransition.h"
#include "./AI//State.h"

#include "./Network/NetworkBase.h"
#include "./Network/GameServer.h"
#include "./Network/GameClient.h"

void TestStateMachine() {
	StateMachine* testMachine = new StateMachine();

	int someData = 0;

	StateFunc AFunc = [](void* data) {
		int* realData = (int*)data;
		(*realData)++;
		spdlog::get("console")->info("In State A!");
	};

	StateFunc BFunc = [](void* data) {
		int* realData = (int*)data;
		(*realData)--;
		spdlog::get("console")->info("In State B!");
	};

	GenericState* stateA = new GenericState(AFunc, (void*)& someData);
	GenericState* stateB = new GenericState(BFunc, (void*)& someData);
	testMachine->AddState(stateA);
	testMachine->AddState(stateB);

	GenericTransition<int&, int>* transitionA = new GenericTransition<int&, int>(GenericTransition<int&, int>::GreaterThanTransition, someData, 10, stateA, stateB);
	GenericTransition<int&, int>* transitionB = new GenericTransition<int&, int>(GenericTransition<int&, int>::GreaterThanTransition, someData, 0, stateB, stateA);

	testMachine->AddTransition(transitionA);
	testMachine->AddTransition(transitionB);

	for (int i = 0; i < 100; ++i) {
		testMachine->Update();
	}

	delete testMachine;
}

int TestNetwork() {
	Logger log("network");
	if (NetworkBase::Initialise() != 0) {
		log.error("An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}

	TestPacketReceiver serverReceiver("Server");
	TestPacketReceiver clientReceiver("Client");

	int port = NetworkBase::GetDefaultPort();

	GameServer* server = new GameServer(port, 1);
	GameClient* client = new GameClient();

	server->RegisterPacketHandler(String_Message, &serverReceiver);
	client->RegisterPacketHandler(String_Message, &clientReceiver);

	bool canConnect = client->Connect(127, 0, 0, 1, port);

	for (int i = 0; i < 10; ++i) {
		server->SendGlobalPacket(
			StringPacket("Server says hello ! " + std::to_string(i)));

		client->SendPacket(
			StringPacket("Client says hello ! " + std::to_string(i)));

		server->UpdateServer();
		client->UpdateClient();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	NetworkBase::Destroy();
}

int main()
{
	Logger* log = new Logger("console");
	log->info("starting State Machine Test");
	TestStateMachine();
	log->info("ending State Machine Test");

	TestNetwork();

	delete log;
}
