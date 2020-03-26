// @Author: Christopher Cometto
#pragma once
#include "KillPlane.h"
#include "TutorialGame.h"

namespace NCL {
	namespace CSC8503 {
		class WinningTriggerPlane : public KillPlane
		{
		public:
			WinningTriggerPlane(PxTransform pos, float xSide, float ySide, float zSide, int scene, TutorialGame* game);
			~WinningTriggerPlane();

			virtual void OnCollisionBegin(GameObject* otherObject) override;

		private:
			vector<GameObject*>	playersCollided;
			TutorialGame* game;
		};
	}
}

