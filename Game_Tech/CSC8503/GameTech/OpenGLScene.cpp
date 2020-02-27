#include "OpenGLScene.h"

#include "..\CSC8503Common\GameObject.h"
#include "..\CSC8503Common\Constraint.h"
#include "../../Common/Camera.h"
#include <algorithm>

using namespace NCL;
using namespace NCL::CSC8503;

NCL::CSC8503::OpenGLScene::OpenGLScene(std::string sceneName)
{
	if (sceneName == "") sceneName = "DefaultScene";
	else this->sceneName = sceneName;
}

NCL::CSC8503::OpenGLScene::~OpenGLScene()
{
	CleanScene();
}

void NCL::CSC8503::OpenGLScene::UpdateViewMatrix(Matrix4 viewMat, int viewID)
{
	viewMatrixArray[viewID] = viewMat;
}

void NCL::CSC8503::OpenGLScene::UpdatePreMatrix(Matrix4 viewMat, int preID)
{
	preMatrixArray[preID] = viewMat;
}

void NCL::CSC8503::OpenGLScene::DeleteObjectByType(GameObject* object)
{
	int tempCount = 0;
	auto iteratorTemp = objArray.begin();
	for (; iteratorTemp != objArray.end(); iteratorTemp++) {
		if ((*iteratorTemp)->getLayerMask() == object->getLayerMask())
		{
			objArray.erase(iteratorTemp);
			objectNum--;
			tempCount++;
		}
	}
	std::cout << "Delete" << tempCount << " objects " << tempCount << std::endl;
}

void NCL::CSC8503::OpenGLScene::DeleteObjectByNum(int objectID)
{
	if (objectID > objectNum)
	{
		std::cout << "Object is not existed" << std::endl;
		return;
	}
	if (objArray[objectID] == NULL)
	{
		std::cout << "Object has been deleted" << std::endl;
		return;
	}

	auto iteratorTemp = objArray.begin();
	objArray.erase(iteratorTemp + objectID - 1 );
	objectNum--;
}

void NCL::CSC8503::OpenGLScene::AddObject(GameObject* newObject)
{
	std::string objectName = newObject->GetName() != "" ? newObject->GetName() :"Default";
	if (newObject->GetRenderObject() == NULL)
	{
		std::cout << objectName << " don't have RenderObject" << std::endl;
	}
	if (newObject->GetPhysicsObject() == NULL)
	{
		std::cout << objectName << " don't have PhysicsObject" << std::endl;
	}
	objArray.push_back(newObject);
	objectNum++;
}

void NCL::CSC8503::OpenGLScene::CleanScene()
{
	for (GameObject* temp : objArray)
	{
		delete temp;
	}
	objArray.clear();
	viewMatrixArray.clear();
	preMatrixArray.clear();

	objectNum = 0;
	isActive  = false;
}
