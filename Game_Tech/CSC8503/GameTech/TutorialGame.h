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
#include "Star.h"
#include "UIPushDownMachine.h"

namespace NCL {
	namespace CSC8503 {
		class TutorialGame		{
		public:
			TutorialGame();
			~TutorialGame();

			virtual void UpdateGame(float dt);

			bool IfQiutGame() { return ifQuitGame; }

			void setPowerUpName(string name) { powerUpName = name; };

			OGLMesh* cubeMesh = nullptr;
			MeshSceneNode* getPlayerMesh(int ID = 0);

			GameObject* AddSphereObjectToWorld(MeshSceneNode* sceneNode, const Vector3& position, const Vector3& size = Vector3(1, 1, 1), std::string objectName = "");
			Player* AddPlayerObjectToWorld(MeshSceneNode* sceneNode, const Vector3& position, const Vector3& size = Vector3(1, 1, 1), std::string objectName = "");
		protected:

			//need check
			//need check
			//need check
			bool SelectObject();
			/*
			void SeenObjects();
			void MoveSelectedObject();
			void DebugObjectMovement();
			void LockedObjectMovement();
			void LockedCameraMovement();
			
			// Stuff from goose game
			GameObject* AddFloorToWorld(const Vector3& position);
			void AddObstacles();
			GameObject* AddTerrainToWorld(const Vector3& position, const Vector3& size, const Vector4& colour);
			GameObject* AddLakeToWorld(const Vector3& position, const Vector3& size, const Vector4& colour);
			void AddBridgeToWorld(Vector3 startPos, int num);
			GameObject* AddSphereToWorld(const Vector3& position, float radius, float inverseMass = 10.0f);
			GameObject* AddCubeToWorld(const Vector3& position, Vector3 dimensions, float inverseMass = 10.0f);
			GameObject* AddPlayerTwoToWorld(const Vector3& position);
			Enemy*		AddParkKeeperToWorld(const Vector3& position);
			GameObject* AddCharacterToWorld(const Vector3& position);
			GameObject* AddAppleToWorld(const Vector3& position);
			GameObject* AddBonusItemToWorld(const Vector3& position);
			

			//GameObject* AddPlayerToWorld(Vector3 position, int playerNum);
			//GameObject* AddOtherPlayerToWorld(Vector3 position, int playerNum);
			GameObject* AddPlayerToWorld(Vector3 position, int playerNum);
			GameObject* AddOtherPlayerToWorld(Vector3 position, int playerNum);
			GameObject* AddGolfLevelToWorld(const Vector3& position, const Vector3& size, const Vector4& colour, int index);
			vector<GameObject*> AddSomeObject(MeshSceneNode* sceneNode, const Vector3& position, const Vector3& size = Vector3(1,1,1), Quaternion rotate = Quaternion(Matrix4::Rotation(0, Vector3(0, 0, 0))), const Vector4& colour = Vector4(1,1,1,1), std::string objectName = "");

			
			Vector3 playerPos1;
			Vector3 playerPos2;
			Vector3 playerPos3;
			Vector3 playerPos4;
			*/


			std::unique_ptr<Logger> log;

			Player* Ball;
			Player* playerTwo;
			//vector<Enemy*> enemies;

			PhysxController physxC = PhysxController::getInstance();

			bool isNetworkedGame;
			bool isServer;

			virtual void UpdateNetworkPostion(GameObject* obj) = 0;
			//GameObject* selectionObject = nullptr;



			//initiate the game
			void InitialiseAssets();
			void InitCamera();
			void InitWorld();
			void StartGame();
			void LoadColladaRenderObjects();
			//sub functions of initiate
			vector<GameObject*> AddSomeObject(MeshSceneNode* sceneNode, const Vector3& position, const Vector3& size = Vector3(1, 1, 1), Quaternion rotate = Quaternion(Matrix4::Rotation(0, Vector3(0, 0, 0))), std::string objectName = "");
			GameObject* AddStarToWorld(Vector3 position);
			
			//update game 
			void UpdateKeys();

			//debugfunction


			//load render objects
			MeshSceneNode* gameMapOrigin;
			MeshSceneNode* gameMapExplode;
			MeshSceneNode* treeFormRhino;
			MeshSceneNode* treeFromBlender;
			MeshSceneNode* treeWithMultiTex;
			MeshSceneNode* powerUpStar;

			MeshSceneNode* playerTemp0;
			MeshSceneNode* playerTemp1;
			MeshSceneNode* playerTemp2;
			MeshSceneNode* playerTemp3;

			//world basic parameters
			GameTechRenderer* renderer;
			GameWorld* world;
			bool inSelectionMode;
			OGLShader* basicShader = nullptr;

			float	forceMagnitude;

			void displayPowerUpText(float dt);
			string powerUpName;
			float powerUpTxtLength;
			float powerUpTxtTimer;

			std::map<int, GameObject*> serverPlayers;
			
			OGLTexture* basicTex	= nullptr;
			OGLTexture* golfLevelTex = nullptr;

			NavigationGrid grid;
			/*
			//Coursework Meshes
			OGLMesh*	gooseMesh	= nullptr;
			OGLMesh*	keeperMesh	= nullptr;
			OGLMesh*	appleMesh	= nullptr;
			OGLMesh*	charA		= nullptr;
			OGLMesh*	charB		= nullptr;
			OGLMesh* testLevel = nullptr;
			OGLMesh* playerMesh1 = nullptr;
			OGLMesh* playerMesh2 = nullptr;
			OGLMesh* playerMesh3 = nullptr;
			OGLMesh* playerMesh4 = nullptr;

			vector<OGLMesh*> golfLevelMeshes;

			//Coursework Additional functionality	
			GameObject* lockedObject	= nullptr;
			Vector3 lockedOffset		= Vector3(0, 14, 20);
			void LockCameraToObject(GameObject* o) {
				lockedObject = o;
			}
			*/
			std::vector<GameObject*> otherplayers;


			//UI system, still fix , do not need check
			
			GameWorld* UIworld;
			GameTechRenderer* UIrenderer;

			UIPushDownMachine* UIMachine;
			UIState* interFace;
			UIState* gameMode;

			UIBar* interBar1;
			UIBar* interBar2;
			UIBar* interBar3;

			UIBar* gameMode1;
			UIBar* gameMode2;
			UIBar* gameMode3;
			UIBar* gameMode4;

			void InitUIWorld();
			void UpdateUIWorld(float dt);
			void UpdateUIKeyWords(UIPushDownMachine* UIMachine);
			void UpdateInGame();
			bool ifQuitGame = false;
			OGLShader* UIShader = nullptr;


		};
	}
}

