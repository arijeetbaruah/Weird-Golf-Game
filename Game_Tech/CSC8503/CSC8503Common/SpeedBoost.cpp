#include "SpeedBoost.h"

SpeedBoost::SpeedBoost(float multiplier, string name) {
	setName(name);
	maxTime = 10;
	this->multiplier = multiplier;
}

void SpeedBoost::Update(float dt) {
	Timed::Update(dt);
	int currShot = st->getShots();
	if (currShot > lastShot) {
		lastShot = currShot;
		PhysicsComponent* pc = po->getComponent<PhysicsComponent*>("PhysicsComponent");
		PxVec3 lvel = pc->getLinearVelocity();
		PxVec3 avel = pc->getAngularVelocity();
		pc->setLinearVelocity(lvel * multiplier);
		pc->setAngularVelocity(avel * multiplier);
	}
}

void SpeedBoost::Remove() {
	po->setCurrentPowerUp(NetworkPowerUps::NONE);
}

void SpeedBoost::Start() {
#ifdef WIN32
	po = dynamic_cast<Player*>(this->getParent());
#else 
	po = (Player*)(this->getParent());
#endif
	st = po->getComponent<ShotTracker*>("ShotTracker");
	lastShot = st->getShots();
}
