#pragma once
#include "PhysicsComponent.h"
class BoxPhysicsComponent : public PhysicsComponent {
public:
	BoxPhysicsComponent(PxTransform transform, GameObject* go, float mass, float xSide, float ySide, float zSide, int scene);

	virtual void Start() override;
	virtual void Update(float dt) override;
};

