// LogTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "./Logger.h"

#include "./StateMachine.h"
#include "./StateTransition.h"
#include "./State.h"



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

int main()
{
	Logger* log = new Logger("console");
	log->info("starting State Machine Test");
	TestStateMachine();
	log->info("ending State Machine Test");

	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}
	atexit(enet_deinitialize);

	ENetAddress address;
	ENetHost* server;
	/* Bind the server to the default localhost.     */
	/* A specific host address can be specified by   */
	/* enet_address_set_host (& address, "x.x.x.x"); */
	address.host = ENET_HOST_ANY;
	/* Bind the server to port 1234. */
	address.port = 1234;
	server = enet_host_create(&address /* the address to bind the server host to */,
		32      /* allow up to 32 clients and/or outgoing connections */,
		2      /* allow up to 2 channels to be used, 0 and 1 */,
		0      /* assume any amount of incoming bandwidth */,
		0      /* assume any amount of outgoing bandwidth */);
	if (server == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}

	enet_host_destroy(server);

	delete log;
}
