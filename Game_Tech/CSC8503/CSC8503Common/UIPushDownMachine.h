//@Author: Yi Han
#pragma once

#include"../GameTech/MeshSceneNode.h"
#include "../CSC8503Common/GameObject.h"
#include"../GameTech/GameTechRenderer.h"
#include "UIState.h"

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




