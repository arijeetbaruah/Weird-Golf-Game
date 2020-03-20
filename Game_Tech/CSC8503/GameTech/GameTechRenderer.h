#pragma once
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

#include "../CSC8503Common/GameWorld.h"

#include "../../Common/stb/stb_image.h"
#include "../../Common/Assets.h"
#include "Player.h"

constexpr float SKY_BOX_ROTATION_SPEED = 0.0005f;

const auto TEXTURE_PATH = NCL::Assets::TEXTUREDIR;

#define SKYBOX_TEXTURES TEXTURE_PATH + "CosmicCoolCloudRight.jpg",TEXTURE_PATH + "CosmicCoolCloudLeft.jpg", \
	TEXTURE_PATH + "CosmicCoolCloudBottom.jpg",TEXTURE_PATH + "CosmicCoolCloudTop.jpg", \
	TEXTURE_PATH + "CosmicCoolCloudFront.jpg",TEXTURE_PATH + "CosmicCoolCloudBack.jpg"

#ifdef _ORBIS
namespace NCL {
	using namespace NCL::Maths;
	namespace Maths {
		class Vector3;
		class Vector4;
	}
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

	namespace Maths {
		class Vector3;
		class Vector4;
	}
	namespace CSC8503 {
		class RenderObject;

		class GameTechRenderer : public OGLRenderer {
		public:
			GameTechRenderer(GameWorld& world);
			~GameTechRenderer();

			void SetBallObject(Player* obj)
			{
				ballObject = obj;
			}
		protected:
			void RenderFrame()	override;

			OGLShader* defaultShader;

			GameWorld& gameWorld;

			void BuildObjectList();
			void SortObjectList();
			void RenderShadowMap();
			void RenderCamera();
			void DrawSkyBox();
			void DrawOcclusion();

			GLuint LoadSkyBox(const std::vector<std::string>& textures);

			void SetupDebugMatrix(OGLShader* s) override;

			vector<const RenderObject*> activeObjects;

			//shadow mapping things
			OGLShader* shadowShader;
			OGLShader* skyboxShader;
			OGLShader* OcclusionShader;
			GLuint		shadowTex;
			GLuint		shadowFBO;
			GLuint		skyboxTex;
			Matrix4     shadowMatrix;

			Vector4		lightColour;
			float		lightRadius;
			Vector3		lightPosition;

			MeshGeometry* quad;

			Player* ballObject = nullptr;

			float offsetX;
		};
	}
}
#endif



