#include "offForward.h"

offForward::offForward() {
	setName("offForward");
	maxShots = 3;
}

void offForward::Update(float dt) {
	LimitedShot::Update(dt);
	int currShot = st->getShots();
	if (currShot > lastShot) {
		lastShot = currShot;
		PhysicsComponent* pc = po->getComponent<PhysicsComponent*>("PhysicsComponent");
		PxVec3 vel = pc->getLinearVelocity();
		pc->setLinearVelocity(PxVec3(vel.z, vel.y, vel.x));
	}
}

void offForward::Remove() {
	po->setCurrentPowerUp(NetworkPowerUps::NONE);
}

void offForward::Start() {
	LimitedShot::Start();
#ifdef WIN32
	po = dynamic_cast<Player*>(this->getParent());
#else 
	po = (Player*)(this->getParent());
#endif
	st = po->getComponent<ShotTracker*>("ShotTracker");
	lastShot = st->getShots();
}
