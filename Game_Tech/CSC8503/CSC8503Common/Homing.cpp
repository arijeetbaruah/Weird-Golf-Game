#include "Homing.h"

Homing::Homing(Vector3 destCoords) {
	setName("Homing");
	maxShots = 5;
	dest = destCoords;
}

void Homing::Apply() {
	Script* sc = new Script();
	sc->setName("HomingScript");
	Vector3 pass = dest;
	sc->setLambda([pass](GameObject* go) {
		std::cout << "Destination " << pass << std::endl;
		SpherePhysicsComponent* spc = go->getComponent<SpherePhysicsComponent*>("SpherePhysicsComponent");
		PxVec3 pvec = spc->getVelocity();
		Vector3 vcel = Vector3(pvec.x, pvec.y, pvec.z);
		vcel.y = 0;
		Vector3 pos = go->GetTransform().GetWorldPosition();
		Vector3 distVec = Vector3(pass.x - pos.x, pass.y - pos.y, pass.z - pos.z);
		float dist = distVec.Length();
		if (dist < 1) { dist = 1; }
		if (vcel.Length() > 3) {
			spc->addForce(PxVec3(distVec.x * (1/dist), 0, distVec.z * (1 / dist)) * 0.005);
		}
	});
	this->getParent()->addComponent(sc);
}

void Homing::Remove() {
	Script* sc = this->getParent()->getComponent<Script*>("HomingScript");
	if (sc != NULL)
		sc->toRemove = true;
}

void Homing::Start() {
	po = dynamic_cast<Player*>(this->getParent());
}
