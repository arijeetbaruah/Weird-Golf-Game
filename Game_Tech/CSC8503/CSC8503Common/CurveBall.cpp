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
		Transform tf = go->GetTransform();
		//spin
		spc->setAngularVelocity(PxVec3(0, direction * 10, 0));

		
		PxVec3 pvec = spc->getVelocity();
		Vector3 vec = Vector3(direction, 0, 0) - tf.GetWorldPosition();
		pvec.y = 0;
		if (pvec.magnitude() > 1) {
			
			spc->addForce(PxVec3(vec.x, vec.y, vec.z) * 0.03);
		}
	});
	po->addComponent(sp);
}

void CurveBall::Remove() {

}

void CurveBall::Start() {
	po = dynamic_cast<Player*>(this->getParent());
}
