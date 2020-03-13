// @Author: Christopher Cometto
#pragma once
#include "../CSC8503Common/Component.h"
#include "PxPhysicsAPI.h"

using namespace NCL;
using namespace CSC8503;
using namespace physx;

class PhysicsComponent : public Component {
public:
	~PhysicsComponent();
	PhysicsComponent(PxTransform transform, GameObject* go);
	void addForce(PxVec3 force);
	void addTorque(PxVec3 torque);

	void setLinearDamping(PxReal value);
	void setAngularDamping(PxReal value);

	PxVec3 getLinearVelocity(); 
	PxVec3 getAngularVelocity();

	void setLinearVelocity(PxVec3);
	void setAngularVelocity(PxVec3);

	PxVec3 getVelocity();

	PxRigidDynamic* getActor() const { return actor; }

	void setAsTrigger();

protected:
	PxRigidDynamic* actor;
	PxPhysics* gPhysics;

	virtual void Start() override;
	virtual void Update(float dt) override;
};

