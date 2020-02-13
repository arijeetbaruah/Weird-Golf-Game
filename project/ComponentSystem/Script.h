#pragma once

#include "Component.h"
#include <functional>

class Script : Component {
	private:
		std::function<void(GameObject*)> lambda;
		std::function<void(GameObject*)> lateLambda;
	
	public:
		void setFunction(std::function<void(GameObject*)> func);
		void nullFunction();
		void Update();
		void LateUpdate();
};