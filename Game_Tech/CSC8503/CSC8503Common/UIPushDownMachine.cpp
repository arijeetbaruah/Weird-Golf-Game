#include "UIPushDownMachine.h"

UIPushDownMachine::UIPushDownMachine()
{
	stateList.clear();
	positions.clear();
	positions.push_back(600);
	positions.push_back(500);
	positions.push_back(400);
	positions.push_back(300);
	positions.push_back(200);
	positions.push_back(100);
	curLeftState = NULL;
	curRightState = NULL;
}

UIPushDownMachine::~UIPushDownMachine()
{
}

void UIPushDownMachine::ResetPositions()
{
	positions.clear();
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
		curLeftState->SetCurrentBar(curLeftState->GetUIList().front());
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






