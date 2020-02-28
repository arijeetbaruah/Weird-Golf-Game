#include "BoxPhysicsComponent.h"

BoxPhysicsComponent::BoxPhysicsComponent(PxTransform transform, float mass, float xSide, float ySide, float zSide)
	: PhysicsComponent("BoxPhysicsComponent") {
	actor = gPhysics->createRigidDynamic(transform);
	PxShape* aBoxShape = PxRigidActorExt::createExclusiveShape(*actor, PxBoxGeometry(xSide / 2, ySide / 2, zSide / 2), *gPhysics->createMaterial(0.5f, 0.5f, 0.6f));
	PxRigidBodyExt::updateMassAndInertia(*actor, mass);
}

void BoxPhysicsComponent::Start() {
	PhysicsComponent::Start();
}

void BoxPhysicsComponent::Update() {
	PhysicsComponent::Update();
}
