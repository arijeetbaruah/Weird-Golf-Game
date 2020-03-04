#include "SpherePhysicsComponent.h"

SpherePhysicsComponent::SpherePhysicsComponent(PxTransform transform, GameObject* go, float mass, float radius)
	: PhysicsComponent("SpherePhysicsComponent", transform, go) {
	PxShape* shape = gPhysics->createShape(PxSphereGeometry(radius), *gPhysics->createMaterial(0.5f, 0.5f, 0.6f));
	actor->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*actor, mass);
}

void SpherePhysicsComponent::Start() {
	PhysicsComponent::Start();
}

void SpherePhysicsComponent::Update() {
	PhysicsComponent::Update();
}
