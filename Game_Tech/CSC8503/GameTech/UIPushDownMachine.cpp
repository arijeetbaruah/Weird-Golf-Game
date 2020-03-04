#include "UIPushDownMachine.h"

UIPushDownMachine::UIPushDownMachine(stateObj* basicState)
{
	currentState = basicState;
	stateList.push(basicState);
}

void UIPushDownMachine::AddState(stateObj* newstate)
{
	if (newstate == stateList.top()) return;
	if (newstate->parentState == stateList.top())
	{
		stateList.push(newstate);
		currentState = newstate;
	}
	else
	{
		while (stateList.size() > 1 || stateList.top() != newstate)
		{
			stateList.pop();
		}
		currentState =  stateList.top();
	}
}

bool UIPushDownMachine::CheckState(stateObj* newState)
{
	return	newState->state == stateList.top()->state;
}

void UIPushDownMachine::BackToBegin()
{
	while (stateList.size() > 1)
	{
		stateList.pop();
	}
}
