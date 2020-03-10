#pragma once
#include "Timed.h"
#include "GameObject.h"
#include "../GameTech/Player.h"

class SpeedBoost : public Timed {
	public:
		SpeedBoost(float multiplier = 2, string name = "SpeedBoost");

		void Apply();
		void Remove();
		void Start();

	protected:
		float origSpeed = 0;
		float multiplier = 2;
		Player* po = nullptr;
};