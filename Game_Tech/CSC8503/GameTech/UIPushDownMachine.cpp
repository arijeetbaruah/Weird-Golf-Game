#include "UIPushDownMachine.h"

void UIPushDownMachine::SetCurrentState(UIState* newState)
{
	curLeftState = newState;
	if (curLeftState->hasSubState()) {
		curRightState = curLeftState->GetCurrentBar()->subState;
	}
}

void UIPushDownMachine::LoadUIState(GameTechRenderer* render)
{
	int leftPos = 0;
	if (curLeftState != NULL){
		for (UIBar* tempBar : curLeftState->GetUIList()) {
			if (curLeftState->GetCurrentBar() != tempBar) render->DrawString(tempBar->words, Vector2(positions[leftPos], verticalPos[0]));
			else render->DrawString(tempBar->words, Vector2(positions[leftPos], verticalPos[0]),Vector4(1,1,1,1));
			leftPos++;
		}
	}
	int rightPos = 0;
	if (curRightState != NULL) {
		for (UIBar* tempBar : curRightState->GetUIList()) {
			render->DrawString(tempBar->words, Vector2(positions[leftPos], verticalPos[1]));
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
		curLeftState->SetCurrentBar(curLeftState->GetLastBar());
	}
}

void UIPushDownMachine::DownBar()
{
	if (curLeftState != NULL)
	{
		curLeftState->SetCurrentBar(curLeftState->GetNextBar());
	}
}
