// LogTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "./Logger/Logger.h"

#include "./AI/StateMachine.h"
#include "./AI//StateTransition.h"
#include "./AI//State.h"



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

	delete log;
}
