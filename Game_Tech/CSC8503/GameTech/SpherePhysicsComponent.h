#pragma once
#include "PhysicsComponent.h"

class SpherePhysicsComponent : public PhysicsComponent {
public:
	SpherePhysicsComponent(PxTransform transform, float mass, float radius);

	virtual void Start() override;
	virtual void Update() override;
};

