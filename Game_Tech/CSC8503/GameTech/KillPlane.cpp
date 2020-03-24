// @Author: Christopher Cometto
#include "KillPlane.h"
#include "BoxPhysicsComponent.h"
#include "PhysxController.h"

NCL::CSC8503::KillPlane::KillPlane(physx::PxTransform pos, float xSide, float ySide, float zSide, int scene)
{
	BoxPhysicsComponent* box = new BoxPhysicsComponent(pos, this, 5, xSide, ySide, zSide, scene);
	box->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	PhysxController::getInstance().setupFiltering(box->getActor(), FilterGroup::eKILLPLANE, FilterGroup::ePLAYER);
	box->setAsTrigger();
	this->addComponent(box);
}

NCL::CSC8503::KillPlane::~KillPlane()
{
}

void NCL::CSC8503::KillPlane::OnCollisionBegin(GameObject* otherObject)
{
	std::cout << "OBJECT DESTROIED" << std::endl;
}
