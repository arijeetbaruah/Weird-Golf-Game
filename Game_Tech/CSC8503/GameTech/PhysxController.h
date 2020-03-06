// @Author: Christopher Cometto
#pragma once

#include <iostream>
#include <vector>
#include "PxPhysicsAPI.h"
#include "CollisionCallback.h"

#define PVD_HOST "127.0.0.1"

using namespace physx;


struct FilterGroup {
	enum Enum {
		ePLAYER = (1 << 0),
		eLEVEL = (1 << 1)
	};
};

// Singleton
class PhysxController {
private:
	static PhysxController* instance;
	PhysxController();

	PxDefaultAllocator gAllocator;
	PxDefaultErrorCallback gErrorCallback;
	PxFoundation* gFoundation = NULL;
	PxPhysics* gPhysics = NULL;
	PxDefaultCpuDispatcher* gDispatcher = NULL;
	PxCooking* gCooking = NULL;
	PxPvd* gPvd = NULL;
	PxScene* actualScene = NULL;
	PxSceneDesc* sceneDesc;

	CollisionCallback callback;
public:
	static PhysxController& getInstance() {
		static PhysxController instance;
		return instance;
	}

	void stepPhysics(bool interactive, float dt);
	void createDefaultScene();
	void addActor(PxActor* actor);

	PxPhysics* Physics() const { return gPhysics; };
	PxCooking* Cooking() const { return gCooking; };

	void setupFiltering(PxRigidActor* actor, PxU32 filterGroup, PxU32 filterMask);
};

