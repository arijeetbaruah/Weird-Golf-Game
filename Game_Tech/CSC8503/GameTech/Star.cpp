#include "Star.h"

using namespace NCL;
using namespace CSC8503;

Star::Star() : GameObject("STAR")
{
	layer = 2;
	layerMask = 1; // Collide with only player

	used = false;
}

Star::~Star() 
{

}

void Star::DuringUpdate(float dt) 
{
	RotateStar(dt);
}

void Star::OnCollisionBegin(GameObject* otherObject)
{
	// Player collision
	if (otherObject->getLayer() == 1)
	{
		if (used)
			return;

		int randNum = rand() % 4 + 1;

		Player* p = dynamic_cast<Player*>(otherObject);

		switch (randNum)
		{
		case 1: p->addComponent(new cubeDebuff(p->GetPlayerMesh(), p->GetCubeMesh()));
			break;
		case 2: p->addComponent(new Homing(Vector3(0, 0, 3)));
			break;
		case 3: p->addComponent(new SpeedBoost());
			break;
		case 4: p->addComponent(new offForward());
			break;
		}

		world->RemoveGameObject(this);

		used = true;
	}
}

void Star::Trigger(GameObject& obj) 
{

}

void Star::RotateStar(float dt)
{

	physx->getActor()->setAngularVelocity(PxVec3(0, 2, 0));
}