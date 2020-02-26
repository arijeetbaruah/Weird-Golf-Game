#include "SpherePhysicsComponent.h"

SpherePhysicsComponent::SpherePhysicsComponent(PxTransform transform, float mass, float radius) 
	: PhysicsComponent("SpherePhysicsComponent") {
	PxShape* shape = gPhysics->createShape(PxSphereGeometry(radius), *gPhysics->createMaterial(0.5f, 0.5f, 0.6f));
	actor = gPhysics->createRigidDynamic(transform);
	actor->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*actor, mass);
}

void SpherePhysicsComponent::Start() {
	PhysicsComponent::Start();
}

void SpherePhysicsComponent::Update() {
	PhysicsComponent::Update();
}
