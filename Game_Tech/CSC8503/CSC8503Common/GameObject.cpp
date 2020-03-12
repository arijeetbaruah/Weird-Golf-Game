#include "GameObject.h"
#include "CollisionDetection.h"

using namespace NCL::CSC8503;

GameObject::GameObject(string objectName)	{
	name			= objectName;
	isActive		= true;
	boundingVolume	= nullptr;
	renderObject	= nullptr;
	networkObject	= nullptr;
}

GameObject::~GameObject()	{
 	delete boundingVolume;
	delete renderObject;
	delete networkObject;
}

void GameObject::DuringUpdate(float dt)
{

}

void GameObject::Trigger(GameObject& obj)
{

}
