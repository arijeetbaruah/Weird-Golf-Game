#include "SceneNode.h"

namespace NCL
{
	void NCL::SceneNode::AddChild(SceneNode* newNode)
	{
		children.push_back(std::move(newNode));
		newNode->parent = this;
		newNode->SetPosition(newNode->position * position.Inverse());
		newNode->SetOrientation(newNode->orientation * orientation.Inverse());
		newNode->SetScale(newNode->scale * scale.Inverse());
	}

	void NCL::SceneNode::Translate(const Vector3& pos)
	{
		position = Matrix4::Translation(position.GetPositionVector() + pos);
	}

	void SceneNode::SetPosition(const Matrix4& pos)
	{
		position = pos;
	}

	void SceneNode::SetOrientation(const Matrix4& rotation)
	{
		orientation = rotation;
	}

	void SceneNode::SetScale(const Matrix4& scale)
	{
		this->scale = scale;
	}

	Matrix4 SceneNode::GetWorldTransform()
	{
		if (parent == nullptr)
		{
			return position * orientation * scale;
		}
		return position * parent->GetWorldPosition() * 
			orientation * parent->GetWorldOrientation() * 
			scale * parent->GetWorldScale();
	}

	Matrix4 SceneNode::GetWorldPosition()
	{
		return position * (parent == nullptr ? Matrix4() : parent->GetWorldPosition());
	}

	Matrix4 SceneNode::GetWorldOrientation()
	{
		return orientation * (parent == nullptr ? Matrix4() : parent->GetWorldOrientation());
	}

	Matrix4 SceneNode::GetWorldScale()
	{
		return scale * (parent == nullptr ? Matrix4() : parent->GetWorldScale());
	}

	void SceneNode::Update()
	{
		for (auto& item : renderObjects)
		{
			auto transform = GetWorldTransform();
			item->SetLocalTransform(GetWorldTransform());
		}
		for (auto& item : children)
		{
			item->Update();
		}
	}
}
