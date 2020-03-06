#include "Star.h"

using namespace NCL;
using namespace CSC8503;

Star::Star() : GameObject("STAR")
{
}

Star::~Star() 
{

}

void Star::DuringUpdate(float dt) 
{
	RotateStar(dt);
}

void Star::Trigger(GameObject& obj) 
{

}

void Star::RotateStar(float dt)
{

	physx->getActor()->setAngularVelocity(PxVec3(0, 2, 0));
}