#pragma once
#include "PowerUp.h"
using namespace NCL;
using namespace CSC8503;
class Targeted : public PowerUp {
	public:
		void setTarget(GameObject* target) {
			this->target = target;
		}
	protected:
		GameObject* target;
};

