#pragma once
#include <stack>

class PushdownState;

class PushdownMachine
{
public:
	PushdownMachine();
	~PushdownMachine();

	void Update();

protected:
	PushdownState* activeState;

	std::stack<PushdownState*> stateStack;
};

