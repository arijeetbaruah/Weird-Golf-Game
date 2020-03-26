// @Author: Christopher Cometto
#include "WinningTriggerPlane.h"

WinningTriggerPlane::WinningTriggerPlane(PxTransform pos, float xSide, float ySide, float zSide, int scene, TutorialGame* game)
	: KillPlane(pos, xSide, ySide, zSide, scene), game(game)
{
	
}

WinningTriggerPlane::~WinningTriggerPlane()
{
}

void WinningTriggerPlane::OnCollisionBegin(GameObject* otherObject)
{
	game->changeLevel();
}
