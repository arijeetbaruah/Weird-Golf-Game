#pragma once
#include "LimitedShot.h"
#include "Script.h"
#include "../GameTech/PhysicsComponent.h"
#include "../GameTech/Player.h"
class CurveBall : public LimitedShot {
	public:
		CurveBall();

		void Apply();
		void Remove();
		void Start();
	private:
		Player* po = nullptr;
};

