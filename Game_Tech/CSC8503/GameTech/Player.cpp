#include "Player.h"
#include "SpherePhysicsComponent.h"
#include "../CSC8503Common/ShotTracker.h"

using namespace NCL;
using namespace CSC8503;

Player::Player(int id) : GameObject("PLAYER")
{
	camOffset = Vector3(0, 15, -10);
	yaw = 0.0f;
	mainCamera = nullptr;

	orbitSpeed = 1.0f;
	orbitDistance = 1.0f;

	playerID = id;

	for (int i = 0; i < 6; i++)
		buttonStates[i] = false;

	layer = 2;
	layerMask = 0; // Collide with everything

	initialMousePos = Vector2(0, 0);

	// Initial cam position
	Vector3 pos = transform.GetWorldPosition();
	Vector4 f = transform.GetWorldMatrix().GetColumn(2);
	Vector3 forward = Vector3(f.x, f.y, f.z);
	camPos = pos;
	camPos -= forward * 1.04;
	camPos.y += 0.5;

	direction = transform.GetWorldPosition() - camPos;
	
	this->addComponent(new ShotTracker());

	testYaw = 0;
}

Player::~Player() 
{

}

void Player::DuringUpdate(float dt)
{
	testYaw += 1;
	Quaternion cameraRot = Quaternion::EulerAnglesToQuaternion(0, testYaw, 0);
	transform.SetLocalOrientation(cameraRot);
	UpdateClientPlayerKeys(dt);

	UpdateCamera(dt);
	std::cout << "Player: " << transform.GetWorldPosition().x << std::endl;
}

void Player::Trigger(GameObject& obj)
{

}


// Handles orbiting the camera around the player
void Player::UpdateCamera(float dt)
{
	float angle = 0.1;

	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::A))
	{
		Vector3 rot;
		rot.x = direction.x * cosf(-angle) + direction.z * sinf(-angle);
		rot.y = direction.y;
		rot.z = -direction.x * sinf(-angle) + direction.z * cosf(-angle);

		direction = rot;
	}

	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::D))
	{
		Vector3 rot;
		rot.x = direction.x * cosf(angle) + direction.z * sinf(angle);
		rot.y = direction.y;
		rot.z = -direction.x * sinf(angle) + direction.z * cosf(angle);

		direction = rot;
	}

	Vector3 pos = transform.GetWorldPosition();

	Vector4 f = transform.GetWorldMatrix().GetColumn(2);

	Vector3 forward = Vector3(f.x, f.y, f.z);

	camPos = pos;
	camPos -= direction;

	Matrix4 temp = Matrix4::BuildViewMatrix(camPos, transform.GetWorldPosition(), Vector3(0, 1, 0));
	Matrix4 modelMat = temp.Inverse();
	Quaternion q(modelMat);
	Vector3 angles = q.ToEuler(); //nearly there now!

	mainCamera->SetPosition(camPos);
	mainCamera->SetPitch(angles.x);
	mainCamera->SetYaw(angles.y);
}


// Handles click and drag movement
void Player::UpdateClientPlayerKeys(float dt)
{
	SpherePhysicsComponent* sphere = (SpherePhysicsComponent*)components.at("SpherePhysicsComponent");

	float x = (float)sphere->getVelocity().x;
	float y = (float)sphere->getVelocity().y;
	float z = (float)sphere->getVelocity().z;

	// Ball can only be moved when standing still
	/*if ((x > 0) || (y > 0) || (z > 0))
		return;*/

	// Gets intitial mouse pos on first click
	if (Window::GetMouse()->ButtonDown(MouseButtons::LEFT) && (initialMousePos.x == 0 && initialMousePos.y == 0))
	{
		initialMousePos = Window::GetMouse()->GetAbsolutePosition();
	}
	else if (!Window::GetMouse()->ButtonDown(MouseButtons::LEFT) && (initialMousePos.x != 0 && initialMousePos.y != 0))
	{
		// Direction 
		Vector2 currentMousePos = Window::GetMouse()->GetAbsolutePosition();
		Vector2 dir = currentMousePos - initialMousePos;

		float distance = dir.Length();

		// Minimum distance
		if (distance < 50) 
		{
			initialMousePos.x = 0;
			initialMousePos.y = 0;
			return;
		}

		dir.Normalise();

		Vector3 threeDimDir = Vector3(-dir.x, 0, -dir.y);

		Quaternion cameraRot = Quaternion::EulerAnglesToQuaternion(0, mainCamera->GetYaw(), 0);

		// Rotate drag direction to match camera direction
		Quaternion q = Quaternion(threeDimDir.x, threeDimDir.y, threeDimDir.z, 0);
		Quaternion c = cameraRot.Conjugate();
		q = cameraRot * q * c;
		shotDir = Vector3(q.x, q.y, q.z);

		Vector3 vec = getShotDir() * distance * speed;
		this->getComponent<ShotTracker*>("ShotTracker")->addShots();
		sphere->addForce(PxVec3(vec.x, vec.y, vec.z));
		

		initialMousePos.x = 0;
		initialMousePos.y = 0;
	}

	if ((initialMousePos.x != 0 && initialMousePos.y != 0))
	{
		// Direction 
		Vector2 currentMousePos = Window::GetMouse()->GetAbsolutePosition();
		Vector2 dir = currentMousePos - initialMousePos;

		Vector4 colour = Vector4(0, 0, 1, 0);

		float distance = dir.Length();

		// Minimum distance
		if (distance < 50)
		{
			colour = Vector4(1, 0, 0, 0);
		}

		//dir.Normalise();

		Vector3 threeDimDir = Vector3(-dir.x, 0, -dir.y);

		Quaternion cameraRot = Quaternion::EulerAnglesToQuaternion(0, mainCamera->GetYaw(), 0);

		// Rotate drag direction to match camera direction
		Quaternion q = Quaternion(threeDimDir.x, threeDimDir.y, threeDimDir.z, 0);
		Quaternion c = cameraRot.Conjugate();
		q = cameraRot * q * c;
		threeDimDir = Vector3(q.x, q.y, q.z);

		threeDimDir.Normalise();
		threeDimDir *= 0.001;

		threeDimDir *= distance;


		Vector3 pos = transform.GetWorldPosition() - threeDimDir;

		Debug::DrawLine(transform.GetWorldPosition(), pos, colour);
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