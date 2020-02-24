#pragma once
#include "OpenGLRendering/OGLRenderer.h"
#include "OpenGLRendering/OGLShader.h"
#include "OpenGLRendering/OGLTexture.h"
#include "OpenGLRendering/OGLMesh.h"

#include "FromGameTech/GameWorld.h"

namespace NCL {
	class Maths::Vector3;
	class Maths::Vector4;
	namespace CSC8503 {
		class RenderObject;

		class GameTechRenderer : public OGLRenderer	{
		public:
			GameTechRenderer(GameWorld& world);
			~GameTechRenderer();

		protected:
			void RenderFrame()	override;

			OGLShader*		defaultShader;

			GameWorld&	gameWorld;

			void BuildObjectList();
			void SortObjectList();
			void RenderShadowMap();
			void RenderCamera(); 

			void SetupDebugMatrix(OGLShader*s) override;

			vector<const RenderObject*> activeObjects;

			//shadow mapping things
			OGLShader*	shadowShader;
			GLuint		shadowTex;
			GLuint		shadowFBO;
			Matrix4     shadowMatrix;

			Vector4		lightColour;
			float		lightRadius;
			Vector3		lightPosition;
		};
	}
}

