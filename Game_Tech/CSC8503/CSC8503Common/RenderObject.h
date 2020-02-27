#pragma once
#include "../../Common/Matrix4.h"
#include "../../Common/TextureBase.h"
#include "../../Common/ShaderBase.h"
#include "../../Common/Vector4.h"
#include <vector>

namespace NCL {
	using namespace NCL::Rendering;

	class MeshGeometry;
	namespace CSC8503 {
		class Transform;
		using namespace Maths;

		class RenderObject
		{
		public:
			RenderObject(Transform* parentTransform, MeshGeometry* mesh, TextureBase* tex, ShaderBase* shader);
			RenderObject(Transform* parentTransform, std::vector<MeshGeometry*> meshList, TextureBase* tex, ShaderBase* shader);
			~RenderObject();

			void SetDefaultTexture(TextureBase* t) {
				texture = t;
			}

			TextureBase* GetDefaultTexture() const {
				return texture;
			}

			MeshGeometry*	GetMesh() const {
				return mesh;
			}
			std::vector<MeshGeometry*> GetMeshList() const{
				return meshList;
			}

			Transform*		GetTransform() const {
				return transform;
			}

			ShaderBase*		GetShader() const {
				return shader;
			}

			void SetColour(const Vector4& c) {
				colour = c;
			}

			Vector4 GetColour() const {
				return colour;
			}

			void SetParentTransform(Transform* parentTransform) {
				this->transform = parentTransform;
			}
		protected:
			MeshGeometry*	mesh;
			TextureBase*	texture;
			ShaderBase*		shader;
			Transform*		transform;
			Vector4			colour;
			std::vector<MeshGeometry*> meshList;
		};
	}
}
