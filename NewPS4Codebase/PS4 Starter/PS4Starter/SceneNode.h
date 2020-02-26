#pragma once
#include <memory>
#include <vector>

#include "../Common/Maths.h"
#include "../Common/Matrix4.h"
#include "EnjoyColladaMesh.h"
#include "RenderObject.h"

using std::shared_ptr;
using std::make_shared;
using std::vector;
using NCL::PS4::RenderObject;

namespace NCL
{
	class SceneNode
	{
	public:
		SceneNode(const char* enjoyPath, 
			Rendering::ShaderBase* shader, 
			Rendering::TextureBase* tex) :
			mesh(make_shared<EnjoyColladaMesh>(enjoyPath))
		{
			for (auto* item : mesh->ChildMeshes)
			{
				renderObjects.push_back(make_shared<RenderObject>(item, shader, tex));
			}
		}
		~SceneNode()
		{
			for (const auto* item : children)
			{
				delete item;
			}
		}

		void AddChild(SceneNode* newNode);

		void Translate(const Vector3& pos);

		void SetPosition(const Matrix4& pos);

		void SetOrientation(const Matrix4& rotation);

		void SetScale(const Matrix4& scale);

		auto GetPosition()
		{
			return position;
		}

		auto GetOrientation()
		{
			return orientation;
		}
		
		auto& GetRenderObjects()
		{
			return renderObjects;
		}

		auto GetWorldTransform();

		Matrix4 GetWorldPosition();

		Matrix4 GetWorldOrientation();

		Matrix4 GetWorldScale();

		void Update();
	protected:
		const shared_ptr<EnjoyColladaMesh> mesh;
		vector<shared_ptr<RenderObject>> renderObjects;
		vector<SceneNode*> children;
		
		Matrix4 position;
		Matrix4 orientation;
		Matrix4 scale;

		SceneNode* parent= nullptr;
	};
}

