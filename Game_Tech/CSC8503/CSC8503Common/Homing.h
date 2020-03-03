#pragma once
#include "LimitedShot.h"
#include "Script.h"
#include "../GameTech/PhysxController.h"
#include "GameObject.h"
#include "Transform.h"
#include <iostream>
#include "../GameTech/Player.h"
#include "../GameTech/SpherePhysicsComponent.h"

class Homing : public LimitedShot {
	public:
		Homing(Vector3);
		void Apply();
		void Remove();
		void Start();

	private:
		Player* po = nullptr;
		Vector3 dest;
};

