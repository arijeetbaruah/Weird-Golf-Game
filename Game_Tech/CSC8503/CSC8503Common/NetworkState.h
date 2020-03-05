#pragma once
#include "../../Common/Vector3.h"
#include "../../Common/Quaternion.h"
#include "../../Common/Vector4.h"

namespace NCL {
	using namespace Maths;
	namespace CSC8503 {
		enum NetworkPowerUps {
			NONE,
			SQUARE
		};

		class GameObject;
		class NetworkState	{
		public:
			NetworkState();
			virtual ~NetworkState();

			int			playerID;
			Vector3		position;
			Vector4		colour;
			Quaternion	orientation;
			int			stateID;
			NetworkPowerUps powerUps;
			bool		valid = false;
		};
	}
}

