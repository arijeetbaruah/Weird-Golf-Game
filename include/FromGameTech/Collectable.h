#pragma once
#include "ComponentSystem/GameObject.h"
#include "Player.h"

		class Collectable : public GameObject
		{
		public:
			Collectable(int p, Vector3 pos);
			~Collectable();
			virtual void Update(float dt);
			virtual void Trigger(GameObject& obj);

			/*void SetConstraint(PositionConstraint* c) { constraint = c; };
			PositionConstraint* GetConstraint() { return constraint; };*/

			Vector3 GetOriginalPosition() { return originalPosition; };

			int GetPoints() { return points; };

		protected:

			//PositionConstraint* constraint;

			Vector3 originalPosition;

			int points;
		};

