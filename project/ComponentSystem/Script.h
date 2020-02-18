#pragma once

#include "Component.h"
#include <functional>

class Script : public Component {
	private:
		std::function<void(GameObject*)> lambda;
		std::function<void(GameObject*)> lateLambda;
	
	public:
		Script();
		Script(std::function<void(GameObject*)> script);
		~Script() {};

		void setLambda(std::function<void(GameObject*)> func);
		void nullLambda();

		void setLateLambda(std::function<void(GameObject*)> func);
		void nullLateLambda();

		void Update();
		void LateUpdate();
};