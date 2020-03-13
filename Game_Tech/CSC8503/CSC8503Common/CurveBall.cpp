#include "CurveBall.h"

CurveBall::CurveBall() {
	setName("CurveBall");
	maxShots = 4;
}

void CurveBall::Apply() {
	Script* sp = new Script();
	sp->setName("Spin");
	int direction = (rand() % 2 + 1 == 1) ? 1 : -1;
	sp->setLambda([direction](GameObject* go) {
		PhysicsComponent* spc = go->getComponent<PhysicsComponent*>("PhysicsComponent");
		
		//spin
		spc->setAngularVelocity(PxVec3(0, direction * 10, 0));

		PxVec3 pvec = spc->getVelocity();
		pvec.y = 0;
		Vector3 vcel = Vector3(pvec.x, pvec.y, pvec.z);

		if (vcel.Length() > 3) {
			spc->addForce(PxVec3(direction, 0, 0) * 0.05);
		}
	});
	po->addComponent(sp);
}

void CurveBall::Remove() {

}

void CurveBall::Start() {
	po = dynamic_cast<Player*>(this->getParent());
}
