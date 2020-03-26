#include "LimitedShot.h"
#include "GameObject.h"
#include "ShotTracker.h"


void LimitedShot::Start() {
	st = ((Player*)this->getParent())->getComponent<ShotTracker*>("ShotTracker");
	lastShot = st->getShots();
}

void LimitedShot::Update(float dt) {
	Targeted::Update(dt);
	int currShot = st->getShots();
	if (currShot > lastShot) {
		lastShot = currShot;
		takenShots++;
	}
}

bool LimitedShot::conditionCheck() {
	return takenShots >= maxShots;
}
