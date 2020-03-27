// @Author: Christopher Cometto
#include "WinningTriggerPlane.h"

WinningTriggerPlane::WinningTriggerPlane(PxTransform pos, float xSide, float ySide, float zSide, int scene, TutorialGame* game)
	: KillPlane(pos, xSide, ySide, zSide, scene), game(game)
{
	setLayer(6);
}

WinningTriggerPlane::~WinningTriggerPlane()
{
}

void WinningTriggerPlane::OnCollisionBegin(GameObject* otherObject)
{
	if (!otherObject->getLayer() == 1 &&
		!otherObject->getLayer() == 5)
		return;

	vector<GameObject*>::iterator it = std::find(playersCollided.begin(), playersCollided.end(), otherObject);

	if (it != playersCollided.end())
		return;

	playersCollided.push_back(otherObject);

	if (playersCollided.size() >= game->currentPlayerCount) 
	{
		game->changeLevel();
		playersCollided.clear();
	}
}
