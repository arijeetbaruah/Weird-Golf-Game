// @Author: Christopher Cometto
#include "PhysicsComponent.h"
#include "../../Common/Vector3.h"
#include "../CSC8503Common/GameObject.h"
#include <iostream>

PhysicsComponent::PhysicsComponent(std::string name) : Component(name) {
	gPhysics = PhysxController::getInstance().Physics();
}

void PhysicsComponent::Start() {
	PhysxController::getInstance().addActor(actor);
}

void PhysicsComponent::Update() {
	PxTransform tran = actor->getGlobalPose();
	std::cout << tran.p.x << tran.p.y << tran.p.z << std::endl;
	getParent()->GetTransform().SetWorldPosition(Vector3(tran.p.x, tran.p.y, tran.p.z));

	// Not really working
	Quaternion orientation = Quaternion(tran.q.x, tran.q.y, tran.q.z, tran.q.w);
	getParent()->GetTransform().SetLocalOrientation(orientation);
}

void PhysicsComponent::addForce(PxVec3 force) {
	actor->addForce(force);
}

void PhysicsComponent::setLinearDamping(PxReal value) {
	actor->setLinearDamping(value);
}

void PhysicsComponent::setAngularDamping(PxReal value) {
	actor->setAngularDamping(value);
}

PxVec3 PhysicsComponent::getVelocity()
{
	return actor->getLinearVelocity() + actor->getAngularVelocity();
	
}