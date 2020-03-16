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

	UIBar* left;
	UIBar* right;

	bool isSelected;
	std::string words;

	UIBar::UIBar(std::string barName){
		funN = NULL;
		funL = NULL;
		subState = NULL;
		isSelected = false;
		words = barName;
		left = NULL;
		right = NULL;
	}
};

class UIState
{
public:
	UIState();
	~UIState();

	void AddBar(UIBar* newBar);

	vector<UIBar*> GetUIList() { return UIList; }

	UIBar* const GetCurrentBar() { return	currentBar; }
	void SetCurrentBar(UIBar* newBar) {currentBar = newBar; }

	bool hasSubState(){
		return currentBar->subState == NULL ? false: true;
	}
	UIBar* GetLeftBar() { return currentBar->left; }
	UIBar* GetRightBar() { return currentBar->right; }

private:
	vector<UIBar*> UIList;
	UIBar* currentBar;
};


class UIPushDownMachine
{
public:
	UIPushDownMachine();
	~UIPushDownMachine();

	void ResetPositions();

	void AddState(UIState* newState) {
		stateList.push_back(newState);
	}
	vector<UIState*> GetStateList() {
		return	stateList;
	}

	void SetCurrentState(UIState* newState);

	void LoadUIState(GameTechRenderer* render);

	void AddPositions(float newPostion){
		positions.push_back(newPostion);
	}
	void SetVertical(float ver1,float ver2) {
		verticalPos[0] = ver1;
		verticalPos[1] = ver2;
	}

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




