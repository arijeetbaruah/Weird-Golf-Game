// @Author: Christopher Cometto
#pragma once
#include "../CSC8503Common/Component.h"
#include "PxPhysicsAPI.h"

using namespace NCL;
using namespace CSC8503;
using namespace physx;

class PhysicsComponent : public Component {
public:
	PhysicsComponent(std::string name, PxTransform transform, GameObject* go);
	void addForce(PxVec3 force);

	void setLinearDamping(PxReal value);
	void setAngularDamping(PxReal value);

	PxVec3 getVelocity();

	PxRigidDynamic* getActor() const { return actor; }
protected:
	PxRigidDynamic* actor;
	PxPhysics* gPhysics;

	virtual void Start() override;
	virtual void Update(float dt) override;

	void setAsTrigger();
};

