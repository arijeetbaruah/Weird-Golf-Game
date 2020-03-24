#pragma once
#include "PhysicsComponent.h"
#include "../CSC8503Common/Transform.h"

class SpherePhysicsComponent : public PhysicsComponent {
public:
	SpherePhysicsComponent(PxTransform transform, GameObject* go, float mass, float radius, PxMaterial* mMaterial, int scene);

	virtual void Start() override;
	virtual void Update(float dt) override;

};

