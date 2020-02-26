#include "cubeDebuff.h"
using namespace NCL;
using namespace CSC8503;
cubeDebuff::cubeDebuff() {
	setName("cubeDebuff");
	maxTime = 30;
	GameObject* par = this->getParent();
	RenderObject* ren = this->getParent()->GetRenderObject();
}

void cubeDebuff::Start() {
	
}

void cubeDebuff::Apply() {
	//par->SetRenderObject(new RenderObject(&par->GetTransform(), , ren->GetDefaultTexture(), ren->GetShader()));
}

void cubeDebuff::Remove() {
	//par->SetRenderObject(new RenderObject(&par->GetTransform(), TutorialGame::sphereMesh, ren->GetDefaultTexture(), ren->GetShader()));
}
