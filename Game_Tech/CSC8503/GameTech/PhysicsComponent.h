// @Author: Christopher Cometto
#pragma once
#include "../CSC8503Common/Component.h"
#include "PhysxController.h"

using namespace NCL;
using namespace CSC8503;

class PhysicsComponent : public Component {
public:
	PhysicsComponent(std::string name);
	void addForce(PxVec3 force);

	void setLinearDamping(PxReal value);
	void setAngularDamping(PxReal value);

protected:
	PxRigidDynamic* actor;
	PxPhysics* gPhysics;

	virtual void Start() override;
	virtual void Update() override;
};

