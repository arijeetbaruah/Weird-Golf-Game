#pragma once
#include "MeshSceneNode.h"
#include "../CSC8503Common/GameObject.h"
#include <map>
#include <vector>
#include<functional>
#include"../../Common/Vector3.h"
#include"GameTechRenderer.h"

typedef void (*UIStateN)();
typedef std::function<void()> UIStateL;

class UIState;

struct UIBar
{
	UIState* subState;
	UIStateN funN;
	UIStateL funL;
	bool isSelected;
	std::string words;

	UIBar::UIBar(std::string barName){
		funN = NULL;
		funL = NULL;
		subState = NULL;
		isSelected = false;
		words = barName;
	}
};

class UIState
{
public:
	UIState();
	~UIState();

	void AddBar();
	void UpdateKeyWords();
	void UseBar();
	vector<UIBar*> GetUIList() { return UIList; }

	UIBar* const GetCurrentBar() { return	currentBar; }
	void SetCurrentBar(UIBar* newBar) {currentBar = newBar; }

	bool hasSubState(){
		return currentBar->subState == NULL ? false: true;
	}
	UIBar* GetLastBar() { return currentBar; }
	UIBar* GetNextBar() { return currentBar; }

private:
	vector<UIBar*> UIList;
	UIBar* currentBar;
};


class UIPushDownMachine
{
public:
	UIPushDownMachine();
	~UIPushDownMachine();

	void AddState(UIState* newState) {
		stateList.push_back(newState);
	}

	void SetCurrentState(UIState* newState);


	void LoadUIState(GameTechRenderer* render);

	void IntoBar();
	void UpBar();
	void DownBar();

private:



	vector<UIState*> stateList;
	UIState* curLeftState;
	UIState* curRightState;
	vector<float> positions;
	float verticalPos[2];

};




