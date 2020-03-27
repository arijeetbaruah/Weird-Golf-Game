#include "SpherePhysicsComponent.h"

SpherePhysicsComponent::SpherePhysicsComponent(PxTransform transform, GameObject* go, float mass, float radius, PxMaterial* mMaterial, int scene)
	: PhysicsComponent(transform, go, scene) {
	PxShape* shape = gPhysics->createShape(PxSphereGeometry(radius), *mMaterial, true);
	shape->setName("Sphere");
	actor->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*actor, mass);
	
}

void SpherePhysicsComponent::Start() {
	PhysicsComponent::Start();
}

void SpherePhysicsComponent::Update(float dt) {
	PhysicsComponent::Update(dt);
}
