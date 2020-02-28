#pragma once
#include "../CSC8503Common/RenderObject.h"
#include "../../Common/MeshGeometry.h"
#include <vector>

using namespace NCL;
using namespace CSC8503;

class MeshSceneNode
{
protected:
	MeshSceneNode* parentNode;
	std::vector<MeshSceneNode*> subNode;
	std::vector<RenderObject*> meshList;

	void GetSubMeshes(std::vector<RenderObject*> &tempMesh, MeshSceneNode* tempNode);

public:

	void AddMesh(RenderObject* mesh) {				meshList.push_back(mesh); }
	void SetParentNode(MeshSceneNode* parentNode) {	this->parentNode = parentNode;	 }
	void AddSubNode(MeshSceneNode* sonNode) {		this->subNode.push_back(sonNode);}
	void DeleteSubNode(MeshSceneNode* oldNode);

	std::vector<RenderObject*> GetAllMesh();
};

