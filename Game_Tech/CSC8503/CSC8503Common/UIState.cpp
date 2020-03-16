#include "UIState.h"


UIState::UIState()
{
	UIList.clear();
	currentBar = NULL;
}

UIState::~UIState()
{
}

void UIState::AddBar(UIBar* newBar)
{
	if (UIList.size() == 0)
	{
		UIList.push_back(newBar);
		newBar->left = newBar->right = newBar;
	}
	else
	{
		UIList.back()->right = newBar;
		newBar->left = UIList.back();
		UIList.push_back(newBar);
		newBar->right = UIList.front();
		UIList.front()->left = UIList.back();
	}
}