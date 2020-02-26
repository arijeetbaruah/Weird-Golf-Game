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

	initialMousePos = Vector2(0, 0);
}

Player::~Player() 
{

}

void Player::DuringUpdate(float dt)
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

	if (Window::GetMouse()->ButtonDown(MouseButtons::LEFT) && (initialMousePos.x == 0 && initialMousePos.y == 0))
	{
		initialMousePos = Window::GetMouse()->GetAbsolutePosition();
	}
	else if (!Window::GetMouse()->ButtonDown(MouseButtons::LEFT) && (initialMousePos.x != 0 && initialMousePos.y != 0))
	{
		Vector2 currentMousePos = Window::GetMouse()->GetAbsolutePosition();
		Vector2 direction = currentMousePos - initialMousePos;

		float distance = direction.Length();

		// Minimum distance
		if (distance < 50) 
		{
			initialMousePos.x = 0;
			initialMousePos.y = 0;
			return;
		}

		direction.Normalise();

		Vector3 threeDimDir = Vector3(direction.x, 0, direction.y);

		// Rotate direction to match current object direction
		Quaternion q = Quaternion(threeDimDir.x, threeDimDir.y, threeDimDir.z, 0);
		Quaternion c = transform.GetLocalOrientation().Conjugate();
		q = transform.GetLocalOrientation() * q * c;
		threeDimDir = Vector3(q.x, q.y, q.z);

		physicsObject->AddForce(threeDimDir * distance * 1000);

		initialMousePos.x = 0;
		initialMousePos.y = 0;
	}
	else if(!Window::GetMouse()->ButtonDown(MouseButtons::LEFT))
	{
		// Camera only rotates when mouse button not pressed down
		yaw -= (Window::GetMouse()->GetRelativePosition().x);

		if (yaw < 0) {
			yaw += 360.0f;
		}
		if (yaw > 360.0f) {
			yaw -= 360.0f;
		}

		transform.SetLocalOrientation(Quaternion::EulerAnglesToQuaternion(0, yaw, 0));
		return;
	}

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