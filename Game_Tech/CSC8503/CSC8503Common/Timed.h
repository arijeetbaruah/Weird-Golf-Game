#pragma once
#include "Targeted.h"
class Timed : public Targeted {
	public:
		void resetTime();
		virtual void Update(float dt);
		bool conditionCheck();
	protected:
		float timeActive = 0;
		float maxTime;
};

