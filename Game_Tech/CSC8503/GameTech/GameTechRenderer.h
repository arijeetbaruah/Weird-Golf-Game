#pragma once
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

#include "../CSC8503Common/GameWorld.h"

#include "../../Common/stb/stb_image.h"
#include "../../Common/Assets.h"
#include "Player.h"

constexpr auto WIDTH = 1280;
constexpr auto HEIGHT = 720;

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
			void SetGameStarted()
			{
				isStarted = true;
			}

			void SetWorld(GameWorld& g) { gameWorld = g; };
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
			void DrawMinimap();
			void AttachMinimap();

			GLuint LoadSkyBox(const std::vector<std::string>& textures);

			void SetupDebugMatrix(OGLShader* s) override;

			vector<const RenderObject*> activeObjects;

			//shadow mapping things
			OGLShader* shadowShader;
			OGLShader* skyboxShader;
			OGLShader* OcclusionShader;
			OGLShader* minimapShader;

			GLuint		shadowTex;
			GLuint		shadowFBO;
			GLuint		skyboxTex;

			GLuint		minimapTex;
			GLuint		minimapDepth;
			GLuint		minimapFBO;

			Matrix4     shadowMatrix;

			Vector4		lightColour;
			float		lightRadius;
			Vector3		lightPosition;

			MeshGeometry* quad;
			OGLMesh* minimapQuad;

			Player* ballObject = nullptr;

			float offsetX;
			
			bool isStarted = false;
			float SkyBoxT = 0.2;
		};
	}
}
#endif



