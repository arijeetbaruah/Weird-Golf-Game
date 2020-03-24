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
		eLEVEL = (1 << 1),
		eSTAR = (1 << 2)
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

	std::vector<PxScene*> scenes;

	CollisionCallback callback;
public:
	static PhysxController& getInstance() {
		static PhysxController instance;
		return instance;
	}

	void addNewScene() 
	{
		PxScene* newScene = gPhysics->createScene(*sceneDesc);
		addScene(newScene);
	}

	void stepPhysics(bool interactive, float dt);
	void createDefaultScene();
	void addActor(PxActor* actor, int index);
	void removeActor(PxActor* actor);
	void addScene(PxScene* scene);
	void setActiveScene(int index);

	PxPhysics* Physics() const { return gPhysics; };
	PxCooking* Cooking() const { return gCooking; };

	void setupFiltering(PxRigidActor* actor, PxU32 filterGroup, PxU32 filterMask);
};

