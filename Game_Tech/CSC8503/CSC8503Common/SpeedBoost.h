#pragma once
#include "Timed.h"
#include "ShotTracker.h"
#include "Script.h"
#include "GameObject.h"
#include "../GameTech/Player.h"
#include "../GameTech/PhysicsComponent.h"

class SpeedBoost : public Timed {
	public:
		SpeedBoost(float multiplier = 2, string name = "SpeedBoost");

		void Apply() {};
		void Update(float dt);
		void Remove();
		void Start();

	protected:
		float multiplier = 2;
		float lastShot = 0;
		ShotTracker* st = nullptr;
		Player* po = nullptr;
};