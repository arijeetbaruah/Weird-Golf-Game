#pragma once

#include "Component.h"
#include <Functional>

namespace NCL {
	namespace CSC8503 {
		class PowerUp: public Component {
			protected:
				virtual void Apply() = 0;
				virtual void remove() = 0;
		};
	}
}

