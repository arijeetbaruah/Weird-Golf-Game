#pragma once
#include "MeshSceneNode.h"
#include "../CSC8503Common/GameObject.h"
#include <stack>
#include <vector>

class UIState;

struct UIFunction
{
	int key;
	void (*funPoint)(void*);
	UIState* subState;
	std::string words;
	UIFunction::UIFunction() {
		key = -1;
		funPoint = NULL;
		words = "";
		subState = NULL;
	}
};

class UIState
{
public:
	void UseFunction(int newKey) {
		for (UIFunction* tempFun : funList)
		{
			if (tempFun->key == newKey && tempFun->funPoint != NULL)	tempFun->funPoint(NULL);
			if (tempFun->subState != NULL)								ShowState(tempFun->subState);
		}
	}

protected:
	void ShowState(UIState*) {}

	vector<UIFunction*> funList;

};

class UIPushDownMachine
{
public:

protected:
	vector<UIState> stateList;
};

