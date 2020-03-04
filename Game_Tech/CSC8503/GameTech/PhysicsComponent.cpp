// @Author: Christopher Cometto
#include "PhysicsComponent.h"
#include "../../Common/Vector3.h"
#include "../CSC8503Common/GameObject.h"
#include "PhysxController.h"
#include <iostream>

PhysicsComponent::PhysicsComponent(std::string name, PxTransform transform, GameObject* go) : Component(name) {
	gPhysics = PhysxController::getInstance().Physics();
	actor = gPhysics->createRigidDynamic(transform);
	actor->userData = go;
}

void PhysicsComponent::Start() {
	PhysxController::getInstance().addActor(actor);
}

void PhysicsComponent::Update() {
	PxTransform tran = actor->getGlobalPose();
	getParent()->GetTransform().SetWorldPosition(Vector3(tran.p.x, tran.p.y, tran.p.z));
}

void PhysicsComponent::setAsTrigger() {
	PxShape* shape;
	actor->getShapes(&shape, 1);
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
}

void PhysicsComponent::addForce(PxVec3 force) {
	actor->addForce(force);
}
