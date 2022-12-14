#include "./AI/StateMachine.h"
#include "./AI/State.h"
#include "./AI/StateTransition.h"

StateMachine::StateMachine()
{
	activeState = nullptr;
}

StateMachine::~StateMachine()
{

}

void StateMachine::AddState(State* s) {
	allStates.emplace_back(s);
	if (activeState == nullptr) {
		activeState = s;
	}
}

void StateMachine::AddTransition(StateTransition* t) {
	allTransitions.insert(std::make_pair(t->GetSourceState(), t));
}

void StateMachine::Update() {
	if (activeState) {
		activeState->Update();
		std::pair<TransitionIterator, TransitionIterator> range = allTransitions.equal_range(activeState);
		for (auto& i = range.first; i != range.second; ++i) {
			if (i->second->CanTransition()) {
				State* newState = i->second->GetDestinationState();
				activeState = newState;
			}
		}
	}
}
