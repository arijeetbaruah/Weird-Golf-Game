#pragma once
#include "PhysicsComponent.h"
class BoxPhysicsComponent : public PhysicsComponent {
public:
	BoxPhysicsComponent(PxTransform transform, float mass, float xSide, float ySide, float zSide);

	virtual void Start() override;
	virtual void Update() override;
};

