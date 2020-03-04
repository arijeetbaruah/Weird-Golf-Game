#pragma once
#include "MeshSceneNode.h"
#include "../CSC8503Common/GameObject.h"
#include <stack>

enum StateType
{
	begin_menu
};

struct stateObj
{
	std::vector<GameObject*> state;
	stateObj* parentState;
	StateType stateType;
	bool operator==(stateObj* object) {
		return	this->stateType == object->stateType;
	}
	stateObj(StateType statetype)
	{
		stateType = statetype;
	}
};

class UIPushDownMachine
{
protected:
	std::stack<stateObj*>	stateList;
	stateObj* currentState;
public:
	UIPushDownMachine(stateObj* basicState);
	void AddState(stateObj* newstate);
	bool CheckState(stateObj* newState);
	void BackToBegin();
	std::vector<GameObject*> GetMenuList() { return currentState->state; }
};

