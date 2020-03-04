#include "SpeedBoost.h"

SpeedBoost::SpeedBoost() {
	setName("SpeedBoost");
	maxTime = 10;
}

void SpeedBoost::Apply() {
	po->setSpeed(origSpeed * 4);
}

void SpeedBoost::Remove() {
	po->setSpeed(origSpeed);
	po = nullptr;
}

void SpeedBoost::Start() {
	po = dynamic_cast<Player*>(this->getParent());
	origSpeed = po->getSpeed();
}
