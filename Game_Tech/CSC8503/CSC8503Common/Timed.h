#pragma once
#include "Targeted.h"
class Timed : public Targeted {
	public:
		void resetTime();
		void virtual Update(float dt);
		bool conditionCheck();
	protected:
		float timeActive = 0;
		float maxTime;
};

