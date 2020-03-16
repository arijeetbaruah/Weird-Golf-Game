#pragma once
#include "../Common/Matrix4.h"
#include "../Common/MeshGeometry.h"

class ShaderBase;
class TextureBase;

namespace NCL {
	namespace Rendering {
		class ShaderBase;
		class TextureBase;
	}
	namespace PS4 {
		class RenderObject	{
		public:
			RenderObject();
			~RenderObject();

			RenderObject(MeshGeometry* m, Rendering::ShaderBase* shader, Rendering::TextureBase* tex);

			void SetDefaultTexture(Rendering::TextureBase* t) {
				textures[0] = t;
			}
			Rendering::TextureBase* GetDefaultTexture() const {
				return textures[0];
			}

			const Maths::Matrix4& GetLocalTransform() const;

			void	SetLocalTransform(const Maths::Matrix4& mat);

			Rendering::ShaderBase* GetShader() const {
				return shader;
			}
			MeshGeometry* GetMesh()
			{
				return mesh;
			}
			Rendering::TextureBase* GetTexture(unsigned int index)
			{
				return textures[index];
			}
		protected:
			static const int TEXTURE_COUNT = 4;

			MeshGeometry*				mesh;
			Rendering::TextureBase*		textures[TEXTURE_COUNT];
			Rendering::ShaderBase*		shader;
			Maths::Matrix4				localTransform;
		};
	}
}
