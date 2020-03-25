#include "sizeChange.h"
#include "Script.h"

sizeChange::sizeChange(float multiplier) {
	setName("sizeChange");
	maxShots = 5;
	mult = multiplier;
}

void sizeChange::Apply() {
	vector<PxShape*> shapes = po->getComponent<PhysicsComponent*>("PhysicsComponent")->getShapes();
	po->GetTransform().SetWorldScale(po->GetTransform().GetLocalScale() * mult);
	po->setSizeScale(mult);
	Vector3 position = po->GetTransform().GetWorldPosition();
	for (PxShape* sh : shapes) {
		if (sh->getName()) {
			if (sh->getName() == "Box") {
				float size = po->boxSize * mult;
				applyTransformation(new BoxPhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), po, 10, size, size, size, pc->getScene()));
			}
			else {
				float size = po->sphereSize * mult;
				PxMaterial* mat = PhysxController::getInstance().Physics()->createMaterial(0.99f, 0.99f, 1);
				applyTransformation(new SpherePhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), po, 10, size, mat, pc->getScene()));
			}
		}
	}
}

void sizeChange::Remove() {
	vector<PxShape*> shapes = po->getComponent<PhysicsComponent*>("PhysicsComponent")->getShapes();
	po->GetTransform().SetWorldScale(po->GetTransform().GetLocalScale() * 1/mult);
	po->setSizeScale(1);
	Vector3 position = po->GetTransform().GetWorldPosition();
	for (PxShape* sh : shapes) {
		if (sh->getName()) {
			if (sh->getName() == "Box") {
				float size = po->boxSize;
				applyTransformation(new BoxPhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), po, 10, size, size, size, pc->getScene()));
			} else {
				float size = po->sphereSize;
				PxMaterial* mat = PhysxController::getInstance().Physics()->createMaterial(0.99f, 0.99f, 1);
				applyTransformation(new SpherePhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), po, 10, size, mat, pc->getScene()));
			}
		}
	}
}

void sizeChange::Start() {
	LimitedShot::Start();
	po = (Player*)this->getParent();
	pc = po->getComponent<PhysicsComponent*>("PhysicsComponent");
}


void sizeChange::applyTransformation(PhysicsComponent* physC) {
	PxVec3 angVec = pc->getAngularVelocity();
	PxVec3 linVec = pc->getLinearVelocity();
	po->RemoveComponent("PhysicsComponent");
	physC->setLinearDamping(0.8);
	physC->setAngularDamping(2);
	physC->setLinearVelocity(linVec);
	physC->setAngularVelocity(angVec);
	po->addComponent(physC);
	pc = po->getComponent<PhysicsComponent*>("PhysicsComponent");
}