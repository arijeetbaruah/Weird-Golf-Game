#include "Player.h"

using namespace NCL;
using namespace CSC8503;

Player::Player(int id) : GameObject("PLAYER")
{
	speed = 500;
	camOffset = Vector3(0, 15, -10);
	yaw = 0.0f;
	mainCamera = nullptr;

	playerID = id;

	for (int i = 0; i < 6; i++)
		buttonStates[i] = false;

	layer = 2;
	layerMask = 0; // Collide with everything
}

Player::~Player() 
{

}

void Player::Update(float dt)
{
	UpdateClientPlayerKeys(dt);

	UpdateCamera(dt);
}

void Player::Trigger(GameObject& obj)
{

}

void Player::UpdateCamera(float dt)
{
	Vector3 pos = transform.GetWorldPosition();

	Vector4 f = transform.GetWorldMatrix().GetColumn(2);

	Vector3 forward = Vector3(f.x, f.y, f.z);

	Vector3 camPos = pos;

	camPos -= forward * 1.04;
	camPos.y += 40;

	Matrix4 temp = Matrix4::BuildViewMatrix(camPos, transform.GetWorldPosition(), Vector3(0, 1, 0));

	Matrix4 modelMat = temp.Inverse();

	Quaternion q(modelMat);
	Vector3 angles = q.ToEuler(); //nearly there now!

	mainCamera->SetPosition(camPos);
	mainCamera->SetPitch(angles.x);
	mainCamera->SetYaw(angles.y);
}

void Player::UpdateClientPlayerKeys(float dt)
{
	yaw -= (Window::GetMouse()->GetRelativePosition().x);

	//Window::GetMouse()->

	if (yaw < 0) {
		yaw += 360.0f;
	}
	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}

	transform.SetLocalOrientation(Quaternion::EulerAnglesToQuaternion(0, yaw, 0));

	/*Vector4 z = transform.GetWorldMatrix().GetColumn(2);

	Vector3 forward = Vector3(z.x, z.y, z.z);

	Vector4 x = transform.GetWorldMatrix().GetColumn(0);

	Vector3 right = Vector3(x.x, x.y, x.z);*/

	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::LBUTTON)) {
		buttonStates[4] = true;
	}
}

void Player::OnCollisionBegin(GameObject* otherObject) {
	if (otherObject->getLayer() == 6)
	{
		// Do something
	}
}

void Player::OnCollisionEnd(GameObject* otherObject) {
	if (otherObject->getLayer() == 6)
	{
		// Do something
	}
}