#pragma once
#include "..//Common/Matrix4.h"
#include "Component.h"

using namespace NCL::Maths;

class Transform : public Component {
	private:
		Matrix4 transformationMatrix;
	
	public:
		Transform() {
			setName("Transform");
			transformationMatrix = Matrix4();
		}

		Transform(Matrix4 transMatrix) {
			setName("Transform");
			transformationMatrix = transMatrix;
		}

		void Update() {};
};