// @Author: Christopher Cometto
#pragma once

#include <vector>
#include "PxPhysicsAPI.h"
#include <iostream>
#define PVD_HOST "127.0.0.1"

using namespace physx;

struct FilterGroup {
	enum Enum {
		eBALL = (1 << 0),
		eLEVEL = (1 << 1),
	};
};

class TestReportCallback : public PxSimulationEventCallback {
	void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) { PX_UNUSED(constraints); PX_UNUSED(count); }
	void onWake(PxActor** actors, PxU32 count) { PX_UNUSED(actors); PX_UNUSED(count); }
	void onSleep(PxActor** actors, PxU32 count) { PX_UNUSED(actors); PX_UNUSED(count); }
	void onTrigger(PxTriggerPair* pairs, PxU32 count) { PX_UNUSED(pairs); PX_UNUSED(count); }
	void onAdvance(const PxRigidBody* const*, const PxTransform*, const PxU32) {}
	void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) {
		PX_UNUSED((pairHeader));
		std::vector<PxContactPairPoint> contactPoints;

		for (PxU32 i = 0; i < nbPairs; i++) {
			std::cout << "a;lskdl;askd;laksdl;aksd" << std::endl;
		}
	}
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

	TestReportCallback testCallback;
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

