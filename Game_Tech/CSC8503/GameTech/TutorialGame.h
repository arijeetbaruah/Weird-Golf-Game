#pragma once
#include "GameTechRenderer.h"
#include "../CSC8503Common/PhysicsSystem.h"
#include "Player.h"
#include "Enemy.h"
#include <stdlib.h>
#include "Collectable.h"
#include <string> 
#include <iostream>
#include <fstream>
#include "ColladaBase.h"
#include "PhysxController.h"
#include "../../Plugins/Logger/Logger.h"
#include "MeshSceneNode.h"
#include "UIPushDownMachine.h"

namespace NCL {
	namespace CSC8503 {
		class TutorialGame		{
		public:
			TutorialGame();
			~TutorialGame();

			virtual void UpdateGame(float dt);


			OGLMesh* cubeMesh = nullptr;
		protected:

			//need check
			//need check
			//need check
			bool SelectObject();
			GameObject* playerTwo;
			bool isNetworkedGame;
			bool isServer;
			virtual void UpdateNetworkPostion(GameObject* obj) = 0;
			std::unique_ptr<Logger> log;
			GameObject* selectionObject = nullptr;



			//initiate the game
			void InitialiseAssets();
			void InitCamera();
			void InitWorld();
			void StartGame();
			void LoadColladaRenderObjects();
			//sub functions of initiate
			vector<GameObject*> AddSomeObject(MeshSceneNode* sceneNode, const Vector3& position, const Vector3& size = Vector3(1, 1, 1), Quaternion rotate = Quaternion(Matrix4::Rotation(0, Vector3(0, 0, 0))), std::string objectName = "");
			GameObject*			AddSphereObjectToWorld(MeshSceneNode* sceneNode, const Vector3& position, const Vector3& size = Vector3(1, 1, 1), std::string objectName = "");
			GameObject*			AddPlayerObjectToWorld(MeshSceneNode* sceneNode, const Vector3& position, const Vector3& size = Vector3(1, 1, 1), std::string objectName = "");

			//update game 
			void UpdateKeys();

			//debugfunction


			//load render objects
			MeshSceneNode* gameMapOrigin;
			MeshSceneNode* gameMapExplode;
			MeshSceneNode* treeFormRhino;
			MeshSceneNode* treeFromBlender;
			MeshSceneNode* treeWithMultiTex;

			MeshSceneNode* playerTemp0;
			MeshSceneNode* playerTemp1;
			MeshSceneNode* playerTemp2;
			MeshSceneNode* playerTemp3;

			//world basic parameters
			GameTechRenderer* renderer;
			GameWorld* world;
			bool inSelectionMode;
			OGLShader* basicShader = nullptr;

			Player* Ball;
			std::vector<GameObject*> otherplayers;







			//UI system, still fix , do not need check
			Camera* UIcamera;
			MeshSceneNode* UIbar;
			vector<GameObject*> AddStripToState(stateObj* state, MeshSceneNode* sceneNode, const Vector3& position, const Vector3& size = Vector3(1, 1, 1), Quaternion rotate = Quaternion(Matrix4::Rotation(0, Vector3(0, 0, 0))), const Vector4& colour = Vector4(1, 1, 1, 1), std::string objectName = "");
			GameWorld* UIworld;
			void InitUIWorld();
			void UpdateUIWorld(float dt);
			UIPushDownMachine*	UImachine;
			GameTechRenderer*	UIrenderer;
			stateObj* beginState;
			OGLShader* UIShader = nullptr;
		};
	}
}

