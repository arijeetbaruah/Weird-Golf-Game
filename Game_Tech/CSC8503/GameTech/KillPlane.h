// @Author: Christopher Cometto
#pragma once
#include "..\CSC8503Common\GameObject.h"
#include "PxPhysicsAPI.h"

using namespace physx;

namespace NCL {
	namespace CSC8503 {
		class KillPlane : public GameObject
		{
		public:
			KillPlane(PxTransform pos, float xSide, float ySide, float zSide, int scene);
			~KillPlane();

			virtual void OnCollisionBegin(GameObject* otherObject) override;
		};
	}
}

