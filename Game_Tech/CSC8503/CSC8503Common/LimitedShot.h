#pragma once
#include "Targeted.h"
#include "ShotTracker.h"
#include "../GameTech/Player.h"
class LimitedShot : public Targeted {
	public:
		void setTakenShots();
		void Start();
		virtual void Update(float dt);
		bool conditionCheck();
	protected:
		int takenShots = 0;
		int maxShots;
		int lastShot;
		ShotTracker* st = nullptr;
};

