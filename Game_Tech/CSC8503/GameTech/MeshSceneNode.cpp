#include "MeshSceneNode.h"

using namespace NCL;
using namespace CSC8503;

void MeshSceneNode::GetSubMeshes(std::vector<RenderObject*> &tempMesh, MeshSceneNode* tempNode)
{
	if (tempNode->subNode.size() != 0)
	{
		for (MeshSceneNode* temp : tempNode->subNode) {
			temp->GetSubMeshes(tempMesh, temp);
		}
	}
	for (RenderObject* temp: tempNode->meshList){
		tempMesh.push_back(temp);
	}
}

void MeshSceneNode::DeleteSubNode(MeshSceneNode* oldNode)
{
	auto tempItr = subNode.begin();
	for (; tempItr != subNode.end(); tempItr++) {
		if (oldNode == (*tempItr)) {
			subNode.erase(tempItr);
			return;
		}
	}
}

std::vector<RenderObject*> MeshSceneNode::GetAllMesh()
{
	std::vector<RenderObject*> tempVec;
	GetSubMeshes(tempVec, this);
	return tempVec;
}
