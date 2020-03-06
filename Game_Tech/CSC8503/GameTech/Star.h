#pragma once
#include "..\CSC8503Common\GameObject.h"
#include "SpherePhysicsComponent.h"
#include "TriangleMeshPhysicsComponent.h"

namespace NCL {
	namespace CSC8503 {
		class Star : public GameObject
		{
		public:
			Star();
			~Star();

			virtual void DuringUpdate(float dt);
			virtual void Trigger(GameObject& obj);

			void setPhysxComponent(SpherePhysicsComponent* component) { physx = component; };

		protected:
			void RotateStar(float dt);

			SpherePhysicsComponent* physx;

			int test;
		};
	}
}

