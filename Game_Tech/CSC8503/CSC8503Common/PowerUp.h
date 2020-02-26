#pragma once

#include "Component.h"
#include <Functional>

using namespace NCL;
using namespace CSC8503;
class PowerUp: public Component {
	protected:
		virtual void Apply() = 0;
		virtual void remove() = 0;
};

