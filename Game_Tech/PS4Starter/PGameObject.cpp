#include "PGameObject.h"

NCL::PS4::PGameObject::PGameObject(std::string objectName)
{
	renderObject = NULL;
	isActive = true;
	name = objectName;
}

NCL::PS4::PGameObject::~PGameObject()
{
}
