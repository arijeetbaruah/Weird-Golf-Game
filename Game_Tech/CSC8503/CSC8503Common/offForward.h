#pragma once
#include "LimitedShot.h"
#include "GameObject.h"
#include "../GameTech/Player.h"
#include "Transform.h"
#include "Script.h"

class offForward : public LimitedShot {
	public:
		offForward();

		void Apply();
		void Remove();
};

