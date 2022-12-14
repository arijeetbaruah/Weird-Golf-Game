// @Author: Christopher Cometto
#include "PhysicsComponent.h"
#include "../../Common/Vector3.h"
#include "../CSC8503Common/GameObject.h"
#include "PhysxController.h"
#include <iostream>

PhysicsComponent::PhysicsComponent(PxTransform transform, GameObject* go, int scene) : Component() {
	gPhysics = PhysxController::getInstance().Physics();
	actor = gPhysics->createRigidDynamic(transform);
	actor->userData = go;
	setName("PhysicsComponent");
	PhysxController::getInstance().addActor(actor, scene);
	this->scene = scene;
	//PhysxController::getInstance().setupFiltering(actor, FilterGroup::eLEVEL, FilterGroup::eLEVEL);
}

PhysicsComponent::~PhysicsComponent() {
	PhysxController::getInstance().removeActor(actor, scene);
}


void PhysicsComponent::Start() {
}

void PhysicsComponent::Update(float dt) {
	PxTransform tran = actor->getGlobalPose();
	getParent()->GetTransform().SetWorldPosition(Vector3(tran.p.x, tran.p.y, tran.p.z));

	Quaternion orientation = Quaternion(tran.q.x, tran.q.y, tran.q.z, tran.q.w);
	getParent()->GetTransform().SetLocalOrientation(orientation);
}

void PhysicsComponent::setAsTrigger() {
	//PxShape* shape;
	//actor->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, true);
	for each (PxShape* shape in getShapes())
	{
		shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
		shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	}
	//actor->getShapes(&shape, 1);
	
}

void PhysicsComponent::addForce(PxVec3 force) {
	actor->addForce(force);
}

void PhysicsComponent::addTorque(PxVec3 torque) {
	actor->addTorque(torque);
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

vector<PxShape*> PhysicsComponent::getShapes() {
	const PxU32 numShapes = actor->getNbShapes();
	PxShape** shapes = (PxShape**)malloc(sizeof(PxShape*) * numShapes);
	actor->getShapes(shapes, numShapes);

	vector<PxShape*> vShapes;
	for (size_t i = 0; i < numShapes; i++) {
		vShapes.push_back(shapes[i]);
	}
	return vShapes;
}
PxVec3 PhysicsComponent::getLinearVelocity() {
	return actor->getLinearVelocity();
}

PxVec3 PhysicsComponent::getAngularVelocity() {
	return actor->getAngularVelocity();
}

void PhysicsComponent::setLinearVelocity(PxVec3 linVec) {
	actor->setLinearVelocity(linVec);
}

void PhysicsComponent::setAngularVelocity(PxVec3 angVec) {
	actor->setAngularVelocity(angVec);
}
