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
	po->setCurrentPowerUp(NetworkPowerUps::NONE);
	po = nullptr;
}

void SpeedBoost::Start() {
#ifdef WIN32
	po = dynamic_cast<Player*>(this->getParent());
#else 
	po = (Player*)(this->getParent());
#endif
	origSpeed = po->getSpeed();
}
