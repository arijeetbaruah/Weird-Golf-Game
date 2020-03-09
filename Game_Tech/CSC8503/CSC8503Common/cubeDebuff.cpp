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
}

void cubeDebuff::Start() {
	par = this->getParent();
	ren = this->getParent()->GetRenderObject();
}


void cubeDebuff::Apply() {
	par->GetTransform().SetWorldScale(Vector3(0.05,0.05,0.05));
	par->SetRenderObject(new RenderObject(&par->GetTransform(), After, ren->GetDefaultTexture(), ren->GetShader()));
	Vector3 position = par->GetTransform().GetWorldPosition();
	par->RemoveComponent("PhysicsComponent");
	par->addComponent(new BoxPhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), par, 10, 0.1, 0.1, 0.1));
}

void cubeDebuff::Remove() {
	par->GetTransform().SetWorldScale(Vector3(1, 1, 1));
	par->SetRenderObject(new RenderObject(&par->GetTransform(), Before, ren->GetDefaultTexture(), ren->GetShader()));
	Vector3 position = par->GetTransform().GetWorldPosition();
	PxMaterial* mMaterial = PhysxController::getInstance().Physics()->createMaterial(0.99f, 0.99f, 1);
	par->RemoveComponent("PhysicsComponent");
	par->addComponent(new SpherePhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), par, 10, 0.05, mMaterial));
}
