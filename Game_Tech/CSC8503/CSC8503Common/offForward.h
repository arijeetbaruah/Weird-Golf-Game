#pragma once
#include "LimitedShot.h"
#include "ShotTracker.h"
#include "GameObject.h"
#include "../GameTech/PhysicsComponent.h"
#include "../GameTech/Player.h"
#include "Transform.h"
#include "Script.h"

class offForward : public LimitedShot {
	public:
		offForward();

		void Update(float dt);
		void Start();
		void Apply() {};
		void Remove();

	private:
		Player* po = nullptr;
		ShotTracker* st = nullptr;
		int lastShot = 0;
};

