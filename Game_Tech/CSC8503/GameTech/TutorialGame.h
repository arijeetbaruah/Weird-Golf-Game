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

			OGLMesh* cubeMesh = nullptr;
			OGLMesh* sphereMesh = nullptr;

			virtual void UpdateGame(float dt);

		protected:
			void InitialiseAssets();

			void InitCamera();
			void UpdateKeys();

			void InitWorld();

			/*
			These are some of the world/object creation functions I created when testing the functionality
			in the module. Feel free to mess around with them to see different objects being created in different
			test scenarios (constraints, collision types, and so on). 
			*/


			bool SelectObject();



			GameObject* AddPlayerToWorld(Vector3 position, int playerNum);





			std::unique_ptr<Logger> log;
			vector<GameObject*> AddSomeObject(MeshSceneNode* sceneNode, const Vector3& position, const Vector3& size = Vector3(1,1,1), Quaternion rotate = Quaternion(Matrix4::Rotation(0, Vector3(0, 0, 0))), std::string objectName = "");
			GameObject* AddSphereObjectToWorld(MeshSceneNode* sceneNode, const Vector3& position, const Vector3& size = Vector3(1, 1, 1), std::string objectName = "");
			Player* Ball;

			GameObject* playerTwo;

			virtual void UpdateNetworkPostion(GameObject* obj) = 0;



			int secondPlayerScore;

			void StartGame();

			bool isNetworkedGame;
			bool isServer;





			GameTechRenderer*	renderer;
			GameWorld*			world;


			bool inSelectionMode;

			GameObject* selectionObject = nullptr;

			
			OGLTexture* golfLevelTex = nullptr;
			OGLShader*	basicShader = nullptr;

			//Coursework Meshes


			OGLMesh* testLevel = nullptr;
			OGLMesh* playerMesh1 = nullptr;

			vector<OGLMesh*> golfLevelMeshes;

			//Coursework Additional functionality	
			GameObject* lockedObject	= nullptr;
			Vector3 lockedOffset		= Vector3(0, 14, 20);
			void LockCameraToObject(GameObject* o) {
				lockedObject = o;
			}


			//load render objects
			void LoadColladaRenderObjects();
			MeshSceneNode* gameMapOrigin;
			MeshSceneNode* gameMapExplode;
			MeshSceneNode* treeFormRhino;
			MeshSceneNode* treeFromBlender;
			MeshSceneNode* treeWithMultiTex;

			MeshSceneNode* playerTemp1;
			MeshSceneNode* playerTemp2;
			MeshSceneNode* playerTemp3;

			//load otherplayers
			std::vector<GameObject*> otherplayers;


			//UI system
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

