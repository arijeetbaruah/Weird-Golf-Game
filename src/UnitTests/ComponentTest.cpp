#include <iostream>
#include <cassert>
#include "ComponentSystem/GameObject.h"
#include "Common/Matrix4.h"
#include "ComponentSystem/Transform.h"

#define ASSERT_WITH_FAILEXIT(COND) do {if (!(COND)) exit(-1);} while(0)

int main() {
	Matrix4 mat = Matrix4::Rotation(30, Vector3(1, 0, 0)) * Matrix4::Rotation(40, Vector3(0, 1, 0)) * Matrix4::Rotation(50, Vector3(0,0,1));
	GameObject go = GameObject(mat);
	Transform* tf = go.getComponent<Transform*>("Transform");
	ASSERT_WITH_FAILEXIT(tf != nullptr && tf->getName() == "Transform");
	std::cout << tf->getRotationVec() << std::endl;
}