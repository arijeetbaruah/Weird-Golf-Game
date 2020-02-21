#include <iostream>
#include <cassert>
#include "ComponentSystem/GameObject.h"
#include "Common/Matrix4.h"
#include "ComponentSystem/Transform.h"

#define ASSERT_WITH_FAILEXIT(COND) do {if (!(COND)) exit(-1);} while(0)
bool positionTest(Transform& tr) {
	return tr.getPositionVec() == Vector3(0, 0, 0);
}

bool positionTestAgainstPos(Transform& tr, Vector3 position) {
	return tr.getPositionVec() == position;
}

bool rotationTest(Transform& tr, Matrix4 mat) {
	return tr.getPositionVec() == Quaternion(mat).ToEuler();
}

int main() {
	Matrix4 mat = Matrix4::Rotation(30, Vector3(1, 0, 0)) * Matrix4::Rotation(40, Vector3(0, 1, 0)) * Matrix4::Rotation(50, Vector3(0,0,1));
	GameObject go = GameObject(mat);
	Transform* tf = go.getComponent<Transform*>("Transform");

	Vector3 transVec = Vector3(10, 11, 12);
	mat = mat * Matrix4::Translation(transVec);
	GameObject go2 = GameObject(mat);
	Transform* tf2 = go2.getComponent<Transform*>("Transform");

	ASSERT_WITH_FAILEXIT(tf != nullptr && tf->getName() == "Transform");
	ASSERT_WITH_FAILEXIT(positionTest(*tf));
	ASSERT_WITH_FAILEXIT(positionTestAgainstPos(*tf2, transVec));
	ASSERT_WITH_FAILEXIT(rotationTest(*tf, mat));
}