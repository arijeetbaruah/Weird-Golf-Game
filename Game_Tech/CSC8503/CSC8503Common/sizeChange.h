#pragma once
#include "LimitedShot.h"
#include "../GameTech/Player.h"
#include "../GameTech/PhysicsComponent.h"
#include "../GameTech/PhysxController.h"
#include "../GameTech/BoxPhysicsComponent.h"
#include "../GameTech/SpherePhysicsComponent.h"

class sizeChange : public LimitedShot {
	public:
		sizeChange(float);

		void Apply();
		void Remove();
		void Start();

		void applyTransformation(PhysicsComponent* physC);
	private:
		Player* po;
		PhysicsComponent* pc;
		float mult;
};