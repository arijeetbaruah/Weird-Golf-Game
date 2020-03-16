//@Author: Yi Han
#pragma once
#include<iostream>
#include <vector>
#include<functional>

using namespace std;

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

	UIBar(std::string barName) {
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
	void SetCurrentBar(UIBar* newBar) { currentBar = newBar; }

	bool hasSubState() {
		return currentBar->subState == NULL ? false : true;
	}
	UIBar* GetLeftBar() { return currentBar->left; }
	UIBar* GetRightBar() { return currentBar->right; }

private:
	vector<UIBar*> UIList;
	UIBar* currentBar;
};
