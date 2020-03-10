#pragma once
#include <move.h>
#include <queue>

#include "../Plugins/PlayStation4/PS4RendererBase.h"
#include "../Plugins/PlayStation4/PS4Input.h"
#include "../Common/Camera.h"
#include "OBJMesh.h"
#include "EnjoyColladaMesh.h"
#include "SceneNode.h"
#include "Light.h"

#define ASSET_DIR "/app0/Assets/"

static const float biasValues[16] =
{
	0.5, 0.0, 0.0, 0.0,
	0.0, 0.5, 0.0, 0.0,
	0.0, 0.0, 0.5, 0.0,
	0.5, 0.5, 0.5, 1.0
};
static const NCL::Maths::Matrix4 biasMatrix(const_cast<float*>(biasValues));

namespace NCL {
	namespace PS4 {
		class ExampleRenderer : public PS4RendererBase
		{
		public:
			ExampleRenderer(PS4Window* window, PS4Input* input);
			~ExampleRenderer();

			void Update(float dt)	 override;
			Camera mainCamera;
		protected:
			void UpdateRotationAmount(float dt);
			void DrawRenderObject(RenderObject* o);
			void	RenderFrame()	override;
			void RenderActiveScene() override;
			void InitDepthBuffer();
			void SwitchToDepthBuffer();
			void DrawShadow();
			void DrawObjectShadow(RenderObject* obj);

			PS4ComputeShader*	computeTest;
			PS4Shader*	defaultShader;
			PS4Mesh*	defaultMesh;
			PS4Texture* defaultTexture;

			NCL::Maths::Matrix4* viewProjMat;
			Gnm::Buffer	cameraBuffer;

			float* computeResult;
			float time;

			PS4Mesh* newMesh;
			OBJMesh* mesh;

			PS4Texture* testlevelTexture;
			PS4Texture* treeTex;

			PS4Input* input;
			int32_t handle;
			SceneNode* golfLevel;
			SceneNode* building;
			SceneNode* tree;

			Light* mainLight;

			PS4ScreenBuffer* depthBuffer;

			PS4Shader* ShadowShader;

			Gnmx::GnmxGfxContext shadowContext;
		};
	}
}

