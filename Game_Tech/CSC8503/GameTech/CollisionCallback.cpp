// @Author: Christopher Cometto
#include "CollisionCallback.h"
#include "../CSC8503Common/GameObject.h"

using namespace NCL;
using namespace CSC8503;

void CollisionCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) {
	PX_UNUSED((pairHeader));
	std::vector<PxContactPairPoint> contactPoints;

	for (PxU32 i = 0; i < nbPairs; i++) {
		PxActor* a1 = pairHeader.actors[0];
		GameObject* go1 = (GameObject*)a1->userData;
		PxActor* a2 = pairHeader.actors[1];
		GameObject* go2 = (GameObject*)a2->userData;
		go1->OnCollisionBegin(go2);
		go2->OnCollisionBegin(go1);
	}
}
