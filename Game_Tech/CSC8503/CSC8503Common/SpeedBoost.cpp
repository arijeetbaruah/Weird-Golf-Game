#include "SpeedBoost.h"

SpeedBoost::SpeedBoost(float multiplier, string name) {
	setName(name);
	maxTime = 10;
	this->multiplier = multiplier;
}

void SpeedBoost::Apply() {
	po->setSpeed(origSpeed * multiplier);
}

void SpeedBoost::Remove() {
	po->setSpeed(origSpeed);
	po = nullptr;
}

void SpeedBoost::Start() {
	po = dynamic_cast<Player*>(this->getParent());
	origSpeed = po->getSpeed();
}
