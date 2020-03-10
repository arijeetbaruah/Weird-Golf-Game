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
#include "PGameObject.h"

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
		};
	}
}

