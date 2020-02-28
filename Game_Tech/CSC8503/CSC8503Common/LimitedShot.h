#pragma once
#include "Targeted.h"
class LimitedShot : public Targeted {
	public:
		void setTakenShots();
		void Start();
		void Update(float dt);
		bool conditionCheck();
	protected:
		int takenShots = 0;
		int maxShots;
		int startingShots = 0;
};

