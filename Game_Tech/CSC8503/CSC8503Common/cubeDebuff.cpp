#include "cubeDebuff.h"
#include "../GameTech/PhysxController.h"
#include "../GameTech/BoxPhysicsComponent.h"
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

	par->SetRenderObject(new RenderObject(&par->GetTransform(), After, ren->GetDefaultTexture(), ren->GetShader()));

	Vector3 position = par->GetTransform().GetWorldPosition();
	//par->addComponent(new BoxPhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), par, 10, 0.00000005, 0.00000005, 0.00000005));
	
}

void cubeDebuff::Remove() {
	par->GetTransform().SetWorldScale(Vector3(1, 1, 1));
	par->SetRenderObject(new RenderObject(&par->GetTransform(), Before, ren->GetDefaultTexture(), ren->GetShader()));
}
