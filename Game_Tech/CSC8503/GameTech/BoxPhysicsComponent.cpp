#include "BoxPhysicsComponent.h"

BoxPhysicsComponent::BoxPhysicsComponent(PxTransform transform, GameObject* go, float mass, float xSide, float ySide, float zSide)
	: PhysicsComponent(transform, go) {
	PxShape* aBoxShape = PxRigidActorExt::createExclusiveShape(*actor, PxBoxGeometry(xSide / 2, ySide / 2, zSide / 2), *gPhysics->createMaterial(0.5f, 0.5f, 0.6f));
	PxRigidBodyExt::updateMassAndInertia(*actor, mass);
	aBoxShape->setName("Box");
}

void BoxPhysicsComponent::Start() {
	PhysicsComponent::Start();
}

void BoxPhysicsComponent::Update(float dt) {
	PhysicsComponent::Update(dt);
}
