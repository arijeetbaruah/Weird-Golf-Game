// @Author: Christopher Cometto
#pragma once

#include <iostream>
#include <vector>
#include "PxPhysicsAPI.h"
#include "../CSC8503Common/GameObject.h"

#define PVD_HOST "127.0.0.1"

using namespace physx;
using namespace NCL;
using namespace CSC8503;

struct FilterGroup {
	enum Enum {
		ePLAYER = (1 << 0),
		eLEVEL = (1 << 1)
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
			PxActor* a1 = pairHeader.actors[0];
			GameObject* go1 = (GameObject*)a1->userData;
			PxActor* a2 = pairHeader.actors[1];
			GameObject* go2 = (GameObject*)a2->userData;
			
			std::cout << go1 << std::endl;
			std::cout << go2 << std::endl;
			std::cout << std::endl;
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

