#include <iostream>
#include <cassert>

#include "AI/StateMachine.h"
#include "AI/StateTransition.h"
#include "AI/State.h"

#define ASSERT_WITH_FAILEXIT(COND) do { if (!(COND)) exit(-1); } while(0)

int main() {
	StateMachine* testMachine = new StateMachine();

	int someData = 0;

	StateFunc AFunc = [](void* data) {
		int* realData = (int*)data;
		(*realData)++;
	};

	StateFunc BFunc = [](void* data) {
		int* realData = (int*)data;
		(*realData)--;
	};

	GenericState* stateA = new GenericState(AFunc, (void*)& someData);
	GenericState* stateB = new GenericState(BFunc, (void*)& someData);
	testMachine->AddState(stateA);
	testMachine->AddState(stateB);

	GenericTransition<int&, int>* transitionA = new GenericTransition<int&, int>(GenericTransition<int&, int>::GreaterThanTransition, someData, 10, stateA, stateB);
	GenericTransition<int&, int>* transitionB = new GenericTransition<int&, int>(GenericTransition<int&, int>::LessThanTransition, someData, 5, stateB, stateA);

	testMachine->AddTransition(transitionA);
	testMachine->AddTransition(transitionB);

	for (int i = 0; i < 100; ++i) {
		testMachine->Update();
		std::cout << someData << std::endl;
	}

	delete testMachine;

	ASSERT_WITH_FAILEXIT(someData == 6);
}