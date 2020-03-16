#include "LimitedShot.h"
#include "GameObject.h"
#include "ShotTracker.h"

void LimitedShot::setTakenShots() {
	startingShots = this->getParent()->getComponent<ShotTracker*>("ShotTracker")->getShots();
}

void LimitedShot::Start() {
	setTakenShots();
}

void LimitedShot::Update(float dt) {
	Targeted::Update(dt);
}

bool LimitedShot::conditionCheck() {
	std::cout << "shots: " << this->getParent()->getComponent<ShotTracker*>("ShotTracker")->getShots() << " " << startingShots + maxShots << std::endl;
	return this->getParent()->getComponent<ShotTracker*>("ShotTracker")->getShots() >= startingShots + maxShots;
}
