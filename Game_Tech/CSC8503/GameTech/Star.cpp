// @Author: Justin Carter
#include "Star.h"

using namespace NCL;
using namespace CSC8503;

Star::Star() : GameObject("STAR")
{
	layer = 2;
	layerMask = 1; // Collide with only player

	// Hole positions for each level
	holePositions[0] = Vector2(-2.7, 1.5);
	holePositions[1] = Vector2(0.02, 3.19);
	holePositions[2] = Vector2(-0.09, 4.5);
	holePositions[3] = Vector2(0, 9.19);
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
			case 1:
			{
				p->addComponent(new cubeDebuff(p->GetPlayerMesh(), p->GetCubeMesh()));
				p->setCurrentPowerUp(NetworkPowerUps::SQUARE);

				if (otherObject->getLayer() == 1)
					game->setPowerUpName("BOXED IN!");
				break;
			}
			case 2: 
			{
				Vector3 pos;
				switch (game->currentWorld)
				{
				case 0: pos = Vector3(holePositions[0].x, transform.GetWorldPosition().y, holePositions[0].y);
					break;
				case 1: pos = Vector3(holePositions[1].x, transform.GetWorldPosition().y, holePositions[1].y);
					break;
				case 2: pos = Vector3(holePositions[2].x, transform.GetWorldPosition().y, holePositions[2].y);
					break;
				case 3: pos = Vector3(holePositions[3].x, transform.GetWorldPosition().y, holePositions[3].y);
					break;
				}

				p->addComponent(new Homing(pos));
				p->setCurrentPowerUp(NetworkPowerUps::HOMING);

				if (otherObject->getLayer() == 1)
					game->setPowerUpName("HOMING BALL!");
				break;
			}
			case 3:
			{
				p->addComponent(new SpeedBoost());
				p->setCurrentPowerUp(NetworkPowerUps::SPEED);

				if (otherObject->getLayer() == 1)
					game->setPowerUpName("SPEED BOOST!");
				break;
			}
			case 4: 
			{
				p->addComponent(new offForward());
				p->setCurrentPowerUp(NetworkPowerUps::DIRECTION);

				if (otherObject->getLayer() == 1)
					game->setPowerUpName("DIRECTION CHANGE!");
				break;
			}
			case 5:
			{
				p->addComponent(new CurveBall());
				p->setCurrentPowerUp(NetworkPowerUps::CURVE);

				if (otherObject->getLayer() == 1)
					game->setPowerUpName("CURVE BALL!");
				break;
			}
			case 6: 
			{
				p->addComponent(new sizeChange(2));
				p->setCurrentPowerUp(NetworkPowerUps::SIZE);

				if (otherObject->getLayer() == 1)
					game->setPowerUpName("BIG BALL!");
				break;
			}
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