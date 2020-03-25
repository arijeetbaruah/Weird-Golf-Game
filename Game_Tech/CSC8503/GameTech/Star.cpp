// @Author: Justin Carter
#include "Star.h"

using namespace NCL;
using namespace CSC8503;

Star::Star() : GameObject("STAR")
{
	layer = 2;
	layerMask = 1; // Collide with only player

}

Star::~Star() 
{

}

void Star::DuringUpdate(float dt) 
{
	if (!this->getComponent<SpherePhysicsComponent*>("PhysicsComponent"))
	{
		world->RemoveGameObject(this);
		
		return;
	}

	RotateStar(dt);
}

void Star::OnCollisionBegin(GameObject* otherObject)
{
	// Player collision
	if (otherObject->getLayer() == 1)
	{

		int randNum = rand() % 4 + 1;
#ifdef WIN32
		Player* p = dynamic_cast<Player*>(otherObject);
#else 
		Player* p = (Player*)(otherObject);
#endif

		switch (randNum)
		{
		case 1: p->addComponent(new cubeDebuff(p->GetPlayerMesh(), p->GetCubeMesh()));
			game->setPowerUpName("BOXED IN!");
			break;
		case 2: p->addComponent(new Homing(Vector3(0, 0, 3)));
			game->setPowerUpName("HOMING BALL!");
			break;
		case 3: p->addComponent(new SpeedBoost());
			game->setPowerUpName("SPEED BOOST!");
			break;
		case 4: p->addComponent(new offForward());
			game->setPowerUpName("DIRECTION CHANGE!");
			break;
		case 5: p->addComponent(new CurveBall());
			game->setPowerUpName("CURVE BALL!");
			break;
		case 6: p->addComponent(new sizeChange(2));
			game->setPowerUpName("BIG BALL!");
			break;
		}

		this->getComponent<SpherePhysicsComponent*>("PhysicsComponent")->toRemove = true;
		
	}
}

void Star::Trigger(GameObject& obj) 
{

}

void Star::RotateStar(float dt)
{

	physx->getActor()->setAngularVelocity(PxVec3(0, 2, 0));
}