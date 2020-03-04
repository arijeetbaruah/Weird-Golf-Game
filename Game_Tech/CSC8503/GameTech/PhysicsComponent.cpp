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
	//PhysxController::getInstance().setupFiltering(actor, FilterGroup::eLEVEL, FilterGroup::eLEVEL);
}

void PhysicsComponent::Start() {
	PhysxController::getInstance().addActor(actor);
}

void PhysicsComponent::Update(float dt) {
	PxTransform tran = actor->getGlobalPose();
	getParent()->GetTransform().SetWorldPosition(Vector3(tran.p.x, tran.p.y, tran.p.z));

	Quaternion orientation = Quaternion(tran.q.x, tran.q.y, tran.q.z, tran.q.w);
	getParent()->GetTransform().SetLocalOrientation(orientation);
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