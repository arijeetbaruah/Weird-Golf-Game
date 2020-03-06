#pragma once
#include "PxPhysicsAPI.h"
#include "../CSC8503Common/GameObject.h"

using namespace NCL;
using namespace CSC8503;
using namespace physx;

class CollisionCallback : public PxSimulationEventCallback {
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

