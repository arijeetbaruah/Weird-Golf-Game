#pragma once
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

#include "../CSC8503Common/GameWorld.h"


#ifdef _ORBIS
namespace NCL {
	using namespace NCL::Maths;
	class Vector3;
	class Vector4;
	namespace CSC8503 {
		class RenderObject;

		class GameTechRenderer{
		public:
			GameTechRenderer(GameWorld& world);
			~GameTechRenderer();

		protected:
			void RenderFrame() {}
			void BuildObjectList() {}
			void SortObjectList() {}
			void RenderShadowMap() {}
			void RenderCamera() {}

			void SetupDebugMatrix(OGLShader* s) {}
		};
	}
}
#else 
namespace NCL {

	class Maths::Vector3;
	class Maths::Vector4;
	namespace CSC8503 {
		class RenderObject;

		class GameTechRenderer : public OGLRenderer {
		public:
			GameTechRenderer(GameWorld& world);
			~GameTechRenderer();

		protected:
			void RenderFrame()	override;

			OGLShader* defaultShader;

			GameWorld& gameWorld;

			void BuildObjectList();
			void SortObjectList();
			void RenderShadowMap();
			void RenderCamera();

			void SetupDebugMatrix(OGLShader* s) override;

			vector<const RenderObject*> activeObjects;

			//shadow mapping things
			OGLShader* shadowShader;
			GLuint		shadowTex;
			GLuint		shadowFBO;
			Matrix4     shadowMatrix;

			Vector4		lightColour;
			float		lightRadius;
			Vector3		lightPosition;
		};
	}
}
#endif



