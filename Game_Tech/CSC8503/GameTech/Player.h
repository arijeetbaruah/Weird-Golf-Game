// @Author: Justin Carter
#pragma once
#include "..\CSC8503Common\GameObject.h"
#include "../../Common/Window.h"
#include "../../Common/Camera.h"
#include <cmath>
#include <list> 
#include <queue>
#include "../CSC8503Common/PhysicsSystem.h"
#include <math.h>
#include <iostream>
#define PI 3.14159265
namespace NCL {
	namespace CSC8503 {
		
		class Player : public GameObject
		{
		public:
			Player(int id);
			~Player();
			//void UpdatePlayer(float dt);
			virtual void DuringUpdate(float dt);
			virtual void Trigger(GameObject& obj);

			void setCamera(Camera* c) { mainCamera = c; };

			float yaw;

			virtual void OnCollisionBegin(GameObject* otherObject);

			virtual void OnCollisionEnd(GameObject* otherObject);

			bool* getButtonStates() { return buttonStates; };
			bool isCurrentPlayer;
			bool isServer;

			Vector3 getShotDir() {
				if (isOffset)
					return Vector3(shotDir.z, shotDir.y, shotDir.x);
				return shotDir;
			}

			void setShotDir(Vector3 v) {
				shotDir = v;
			}

			void setIsOffset(bool b) {
				isOffset = b;
			}

			float getSpeed() { return speed; }
			void setSpeed(float s) { speed = s; }

			int getID() { return playerID; }

			Vector3 getForceState() { return forceState; }
			void resetForceState() { forceState = Vector3(); }
			void setSizeScale(float s) { sizeScale = s; }
			float getSizeScale() { return sizeScale; }

			float boxSize = 0.1;
			float sphereSize = 0.05;

			void setCurrentPowerUp(NetworkPowerUps p) { power = p; };
			NetworkPowerUps getCurrentPowerUp() { return power; };
			
		protected:

			void UpdateClientPlayerKeys(float dt);
			void UpdateCamera(float dt);

			float orbitSpeed;
			float orbitDistance;
			float speed = 0.005;
			float sizeScale = 1;

			bool isOffset = false;

			Vector3 camPos;
			Vector3 direction;
			Vector3 shotDir;

			Vector2 initialMousePos;

			//vector<GameObject> collectables;
			Camera* mainCamera;
			Vector3 camOffset;
			int playerID;

			NetworkPowerUps power;

			int testYaw;

			bool buttonStates[6];
			Vector3 forceState;

			std::queue<GameObject*> collectables;
		};
	}
}
