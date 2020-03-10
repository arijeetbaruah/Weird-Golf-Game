#include "cubeDebuff.h"
#include "../GameTech/PhysxController.h"
#include "../GameTech/BoxPhysicsComponent.h"
#include "../GameTech/SpherePhysicsComponent.h"
#include "Transform.h"

using namespace NCL;
using namespace CSC8503;
cubeDebuff::cubeDebuff(OGLMesh* before, OGLMesh* after) {
	setName("cubeDebuff");
	maxTime = 5;
	this->Before = before;
	this->After = after;
	mat = PhysxController::getInstance().Physics()->createMaterial(0.99f, 0.99f, 1);
}

void cubeDebuff::Start() {
	par = this->getParent();
	ren = this->getParent()->GetRenderObject();
}


void cubeDebuff::Apply() {
	Vector3 position = par->GetTransform().GetWorldPosition();
	applyTransformation(Vector3(0.05, 0.05, 0.05), After, new BoxPhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), par, 10, 0.1, 0.1, 0.1));
}

void cubeDebuff::Remove() {
	Vector3 position = par->GetTransform().GetWorldPosition();
	applyTransformation(Vector3 (1,1,1), Before, new SpherePhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), par, 10, 0.05, mat));
}

void cubeDebuff::applyTransformation(Vector3 scale, OGLMesh* mesh, PhysicsComponent* physC) {
	par->GetTransform().SetWorldScale(scale);
	par->SetRenderObject(new RenderObject(&par->GetTransform(), mesh, ren->GetDefaultTexture(), ren->GetShader()));
	PhysicsComponent* pc = par->getComponent<PhysicsComponent*>("PhysicsComponent");
	PxVec3 angVec = pc->getAngularVelocity();
	PxVec3 linVec = pc->getLinearVelocity();
	par->RemoveComponent("PhysicsComponent");
	physC->setLinearDamping(0.8);
	physC->setAngularDamping(2);
	physC->setLinearVelocity(linVec);
	physC->setAngularVelocity(angVec);
	par->addComponent(physC);
}