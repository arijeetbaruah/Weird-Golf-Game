#pragma once
#include "..\CSC8503Common\GameObject.h"
#include "../../Common/Window.h"
#include "../../Common/Camera.h"
#include <cmath>
#include <list> 
#include <queue>
#include "Collectable.h"
#define PI 3.14159265
namespace NCL {
	namespace CSC8503 {
		class Player : public GameObject
		{
		public:
			Player(int id);
			~Player();
			//void UpdatePlayer(float dt);
			virtual void Update(float dt);
			virtual void Trigger(GameObject& obj);

			void setCamera(Camera* c) { mainCamera = c; };

			float yaw;

			std::queue<GameObject*>& getCollectables() { return collectables; };

			virtual void OnCollisionBegin(GameObject* otherObject);

			virtual void OnCollisionEnd(GameObject* otherObject);

			bool* getButtonStates() { return buttonStates; };
			
		protected:
			void UpdateClientPlayerKeys(float dt);
			void UpdateCamera(float dt);
			float speed;

			Vector2 initialMousePos;

			//vector<GameObject> collectables;
			Camera* mainCamera;
			Vector3 camOffset;
			int playerID;

			bool buttonStates[6];

			std::queue<GameObject*> collectables;
		};
	}
}
