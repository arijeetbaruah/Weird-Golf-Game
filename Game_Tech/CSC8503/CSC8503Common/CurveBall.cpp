#include "CurveBall.h"

CurveBall::CurveBall() {
	setName("CurveBall");
	maxShots = 5;
}

void CurveBall::Apply() {
	Script* sp = new Script();
	sp->setName("Spin");
	int direction = (rand() % 2 + 1 == 1) ? 1 : -1;
	sp->setLambda([direction](GameObject* go) {
		PhysicsComponent* spc = go->getComponent<PhysicsComponent*>("PhysicsComponent");
		Transform tf = go->GetTransform();
		//spin
		spc->setAngularVelocity(PxVec3(0, direction * 10, 0));
		
		PxVec3 pvec = spc->getVelocity();
		pvec.y = 0;
		float ang = 120;
		PxVec3 curve = PxVec3(pvec.x * cos(ang) - pvec.z * sin(ang), 0, pvec.x * sin(ang) + pvec.z * cos(ang));
		curve = curve - pvec;
		if (pvec.magnitude() > 1) {
			spc->addForce(curve * 0.03);
		}
	});
	po->addComponent(sp);
}

void CurveBall::Remove() {
	Script* sp = this->getParent()->getComponent<Script*>("Spin");
	if (sp != NULL)
		sp->toRemove = true;
}

void CurveBall::Start() {
	LimitedShot::Start();
	po = dynamic_cast<Player*>(this->getParent());
}
