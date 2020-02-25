// @Author: Christopher Cometto
#pragma once
#include "Component.h"
#include "PhysxController.h"

class PhysicsComponent : public Component {
public:
	PhysicsComponent(std::string name);
	void addForce(PxVec3 force);
protected:
	PxRigidDynamic* actor;
	PxPhysics* gPhysics;

	virtual void Start() override;
	virtual void Update() override;
};

