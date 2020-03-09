#include "SpherePhysicsComponent.h"

SpherePhysicsComponent::SpherePhysicsComponent(PxTransform transform, GameObject* go, float mass, float radius, PxMaterial* mMaterial)
	: PhysicsComponent(transform, go) {
	PxShape* shape = gPhysics->createShape(PxSphereGeometry(radius), *mMaterial);
	actor->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*actor, mass);
}

void SpherePhysicsComponent::Start() {
	PhysicsComponent::Start();
}

void SpherePhysicsComponent::Update(float dt) {
	PhysicsComponent::Update(dt);
}
