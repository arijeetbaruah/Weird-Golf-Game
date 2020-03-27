// @Author: Christopher Cometto
#include "KillPlane.h"
#include "BoxPhysicsComponent.h"
#include "PhysxController.h"

KillPlane::KillPlane(physx::PxTransform pos, float xSide, float ySide, float zSide, int scene) : GameObject("KILL PLANE")
{
	BoxPhysicsComponent* box = new BoxPhysicsComponent(pos, this, 10000000000000000000, xSide, ySide, zSide, scene);
	box->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	this->addComponent(box);
}

KillPlane::~KillPlane()
{
	this->RemoveComponent("PhysicsComponent");
}

void KillPlane::OnCollisionBegin(GameObject* otherObject)
{
	std::cout << "OBJECT DESTROIED" << std::endl;
}
