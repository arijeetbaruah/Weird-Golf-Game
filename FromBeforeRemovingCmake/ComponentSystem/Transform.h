#pragma once
#include "Common/Matrix4.h"
#include "Common/Vector3.h"
#include "Common/Vector4.h"
#include "Common/Maths.h"
#include "Common/Quaternion.h"
#include "Component.h"

//@Author: David Towers

using namespace NCL::Maths;

class Transform : public Component {
	private:
		Matrix4 transformationMatrix;
	
	public:
		Transform();

		Transform(Matrix4 transMatrix);

		Vector3 getPositionVec();
		Vector3 getRotationVec();

		void Update() {};
};