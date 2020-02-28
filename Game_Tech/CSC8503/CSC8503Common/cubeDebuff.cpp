#include "cubeDebuff.h"

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
	par->GetTransform().SetWorldScale(Vector3(0.05, 0.05, 0.05));
	par->SetRenderObject(new RenderObject(&par->GetTransform(), After, ren->GetDefaultTexture(), ren->GetShader()));
}

void cubeDebuff::Remove() {
	par->GetTransform().SetWorldScale(Vector3(1, 1, 1));
	par->SetRenderObject(new RenderObject(&par->GetTransform(), Before, ren->GetDefaultTexture(), ren->GetShader()));
}
