#include "ComponentSystem/Transform.h"

Transform::Transform() {
	setName("Transform");
	transformationMatrix = Matrix4();
}

Transform::Transform(Matrix4 transMatrix) {
	setName("Transform");
	transformationMatrix = transMatrix;
}

Vector3 Transform::getPositionVec() {
	return transformationMatrix.GetPositionVector();
}

Vector3 Transform::getRotationVec() {
	float z = 0, y = 0, x = 0, origZ = 0;
	Vector4 row1 = transformationMatrix.GetRow(0);
	Vector4 row2 = transformationMatrix.GetRow(1);
	Vector4 row3 = transformationMatrix.GetRow(2);

	float sinX = -row2.z;
	if (sinX >= 1) {
		x = 90;
	}
	else if (sinX <= -1) {
		x = -90;
	}
	else {
		x = RadiansToDegrees(asin(sinX));
	}

	if (sinX < -0.9999 || sinX > 0.9999) {
		y = RadiansToDegrees(atan2(-row3.x, row1.x));
		z = 0;
	}
	else {
		y = RadiansToDegrees(atan2(row1.z, row3.z));
		z = RadiansToDegrees(atan2(row2.x, row2.y));
	}
	return Vector3(x, y, z);
}
