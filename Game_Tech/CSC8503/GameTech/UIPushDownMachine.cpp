#include "UIPushDownMachine.h"

UIPushDownMachine::UIPushDownMachine()
{
	stateList.clear();
	positions.clear();
	curLeftState = NULL;
	curRightState = NULL;
}

UIPushDownMachine::~UIPushDownMachine()
{
}

void UIPushDownMachine::SetCurrentState(UIState* newState)
{
	curLeftState = newState;
	if (curLeftState->hasSubState()) {
		curRightState = curLeftState->GetCurrentBar()->subState;
	}
	else
	{
		curRightState = NULL;
	}
}

void UIPushDownMachine::LoadUIState(GameTechRenderer* render)
{
	int leftPos = 0;
	if (curLeftState != NULL){
		for (UIBar* tempBar : curLeftState->GetUIList()) {
			if (curLeftState->GetCurrentBar() != tempBar) render->DrawString(tempBar->words, Vector2(verticalPos[0], positions[leftPos]));
			else {
				render->DrawString(tempBar->words, Vector2(verticalPos[0], positions[leftPos]), Vector4(1, 0, 0, 1));
			}
			leftPos++;
		}
	}
	int rightPos = 0;
	if (curRightState != NULL) {
		for (UIBar* tempBar : curRightState->GetUIList()) {
			render->DrawString(tempBar->words, Vector2(verticalPos[1], positions[rightPos]));
			rightPos++;
		}
	}
}

void UIPushDownMachine::IntoBar()
{
	if (curLeftState != NULL)
	{
		UIBar* tempBar = curLeftState->GetCurrentBar();
		if (tempBar->subState != NULL)
		{
			SetCurrentState(tempBar->subState);
		}
		else if (tempBar->funL != NULL)
		{
			tempBar->funL();
		}
		else if (tempBar->funN != NULL)
		{
			tempBar->funN();
		}
	}
}

void UIPushDownMachine::UpBar()
{
	if (curLeftState != NULL)
	{
		curLeftState->SetCurrentBar(curLeftState->GetLeftBar());
		if (curLeftState->hasSubState())
		{
			curRightState = curLeftState->GetCurrentBar()->subState;
		}
		else
		{
			curRightState = NULL;
		}
	}
}

void UIPushDownMachine::DownBar()
{
	if (curLeftState != NULL)
	{
		curLeftState->SetCurrentBar(curLeftState->GetRightBar());
		if (curLeftState->hasSubState())
		{
			curRightState = curLeftState->GetCurrentBar()->subState;
		}
		else
		{
			curRightState = NULL;
		}
	}
}






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
