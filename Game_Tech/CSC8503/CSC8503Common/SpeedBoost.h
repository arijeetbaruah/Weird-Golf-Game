#pragma once
#include "Timed.h"
#include "GameObject.h"
#include "../GameTech/Player.h"

class SpeedBoost : public Timed {
	public:
		SpeedBoost();

		void Apply();
		void Remove();
		void Start();

	protected:
		float origSpeed = 0;
		Player* po = nullptr;
};