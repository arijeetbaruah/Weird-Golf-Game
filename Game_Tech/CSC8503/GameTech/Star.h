#pragma once
#include "..\CSC8503Common\GameObject.h"
#include "SpherePhysicsComponent.h"
#include "TriangleMeshPhysicsComponent.h"
#include "../CSC8503Common/cubeDebuff.h"
#include "../CSC8503Common/SpeedBoost.h"
#include "../CSC8503Common/Homing.h"
#include "../CSC8503Common/PowerUp.h"
#include "../CSC8503Common/offForward.h"
#include <stdlib.h> 
#include "Player.h"
#include "../CSC8503Common/GameWorld.h"

namespace NCL {
	namespace CSC8503 {
		class Star : public GameObject
		{
		public:
			Star();
			~Star();

			virtual void DuringUpdate(float dt);
			virtual void Trigger(GameObject& obj);
			virtual void OnCollisionBegin(GameObject* otherObject);

			void setPhysxComponent(SpherePhysicsComponent* component) { physx = component; };

			void setGameWorld(GameWorld* w) { world = w; };

		protected:
			void RotateStar(float dt);

			SpherePhysicsComponent* physx;

			vector<PowerUp*> powerUps;

			bool used;

			GameWorld* world;
		};
	}
}

