// @Author: Christopher Cometto
#include "PhysicsComponent.h"
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
}

void PhysicsComponent::addForce(PxVec3 force) {
	actor->addForce(force);
}
