#include "SpherePhysicsComponent.h"

SpherePhysicsComponent::SpherePhysicsComponent(PxTransform transform, float mass, float radius, PxMaterial* mMaterial)
	: PhysicsComponent("SpherePhysicsComponent") {
	PxShape* shape = gPhysics->createShape(PxSphereGeometry(radius), *mMaterial);
	actor = gPhysics->createRigidDynamic(transform);
	actor->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*actor, mass);
}

void SpherePhysicsComponent::Start() {
	PhysicsComponent::Start();
}

void SpherePhysicsComponent::Update(float dt) {
	PhysicsComponent::Update(dt);
}
