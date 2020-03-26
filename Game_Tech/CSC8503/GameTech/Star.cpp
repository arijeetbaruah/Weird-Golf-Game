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
		for (int i = 0; i < world->starList.size(); i++)
		{
			if (world->starList[i] == this)
				world->starList[i] = nullptr;
		}
		
		return;
	}
	else 
	{
		RotateStar(dt);
		physx->getActor()->setLinearVelocity(PxVec3(0, 0, 0));
	}

	
}

void Star::OnCollisionBegin(GameObject* otherObject)
{
	// Player collision
	if (otherObject->getLayer() == 1 ||
		otherObject->getLayer() == 5)
	{


		
#ifdef WIN32
		Player* p = dynamic_cast<Player*>(otherObject);
#else 
		Player* p = (Player*)(otherObject);
#endif
		if (p->getCurrentPowerUp() != NetworkPowerUps::NONE)
			return;

		int randNum = rand() % 6 + 1;

		switch (randNum)
		{
		case 1: p->addComponent(new cubeDebuff(p->GetPlayerMesh(), p->GetCubeMesh()));
			p->setCurrentPowerUp(NetworkPowerUps::SQUARE);

			if (otherObject->getLayer() == 1)
				game->setPowerUpName("BOXED IN!");
			break;
		case 2: p->addComponent(new Homing(Vector3(0, 0, 3)));
			p->setCurrentPowerUp(NetworkPowerUps::HOMING);

			if (otherObject->getLayer() == 1)
				game->setPowerUpName("HOMING BALL!");
			break;
		case 3: p->addComponent(new SpeedBoost());
			p->setCurrentPowerUp(NetworkPowerUps::SPEED);

			if (otherObject->getLayer() == 1)
				game->setPowerUpName("SPEED BOOST!");
			break;
		case 4: p->addComponent(new offForward());
			p->setCurrentPowerUp(NetworkPowerUps::DIRECTION);

			if (otherObject->getLayer() == 1)
				game->setPowerUpName("DIRECTION CHANGE!");
			break;
		case 5: p->addComponent(new CurveBall());
			p->setCurrentPowerUp(NetworkPowerUps::CURVE);

			if (otherObject->getLayer() == 1)
				game->setPowerUpName("CURVE BALL!");
			break;
		case 6: p->addComponent(new sizeChange(2));
			p->setCurrentPowerUp(NetworkPowerUps::SIZE);

			if (otherObject->getLayer() == 1)
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