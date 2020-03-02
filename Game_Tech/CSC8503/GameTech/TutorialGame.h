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
#include "PhysxController.h"
#include "ColladaBase.h"
#include "PhysxController.h"
#include "../../Plugins/Logger/Logger.h"
#include "MeshSceneNode.h"

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
			void ResetCamera();
			void UpdateKeys();

			void InitWorld();

			/*
			These are some of the world/object creation functions I created when testing the functionality
			in the module. Feel free to mess around with them to see different objects being created in different
			test scenarios (constraints, collision types, and so on). 
			*/
			void InitSphereGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, float radius);
			void InitMixedGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing);
			void InitCubeGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, const Vector3& cubeDims);
			void SimpleGJKTest();

			bool SelectObject();
			void SeenObjects();
			void MoveSelectedObject();
			void DebugObjectMovement();
			void LockedObjectMovement();
			void LockedCameraMovement();
			/*
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
			*/

			GameObject* AddPlayerToWorld(Vector3 position, int playerNum);
			GameObject* AddOtherPlayerToWorld(Vector3 position, int playerNum);

			Vector3 playerPos1;
			Vector3 playerPos2;
			Vector3 playerPos3;
			Vector3 playerPos4;

			GameObject* AddGolfLevelToWorld(const Vector3& position, const Vector3& size, const Vector4& colour, int index);

			std::unique_ptr<Logger> log;
			vector<GameObject*> AddSomeObject(MeshSceneNode* sceneNode, const Vector3& position, const Vector3& size = Vector3(1,1,1), Quaternion rotate = Quaternion(Matrix4::Rotation(0, Vector3(0, 0, 0))), const Vector4& colour = Vector4(1,1,1,1), std::string objectName = "");

			Player* Ball;
			GameObject* playerTwo;
			vector<Enemy*> enemies;

			PhysxController physxC = PhysxController::getInstance();

			virtual void UpdateNetworkPostion(GameObject* obj) = 0;

			void StoreHighScore();
			std::string fileName;

			int secondPlayerScore;

			void RenderMenu();
			void RenderScoreBoard();
			int buttonSelected;
			bool playing;
			void StartGame();

			bool isNetworkedGame;
			bool isServer;
			int playerID;

			void RestartNetworkedGame();

			bool newSession;

			float matchTimer;
			float gameOverScreenCoolDown;

			GameTechRenderer*	renderer;
			PhysicsSystem*		physics;
			GameWorld*			world;

			bool useGravity;
			bool inSelectionMode;

			float	forceMagnitude;

			GameObject* selectionObject = nullptr;

			
			OGLTexture* basicTex	= nullptr;
			OGLTexture* golfLevelTex = nullptr;
			OGLShader*	basicShader = nullptr;

			NavigationGrid grid;

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

			void LoadColladaRenderObjects();


			//list of renderObject
			MeshSceneNode* GameLevelMapMesh1;
			MeshSceneNode* GameLevelMapMesh2;
			MeshSceneNode* GameLevelMapMesh3;
			MeshSceneNode* GameLevelMapMesh4;
			MeshSceneNode* GameLevelMapMesh5;
			PhysicsObject* temp;

			//list of 
			GameObject* gameLevelOBJ;

			//list of mesh
			OGLMesh* playerMesh = nullptr;


		};
	}
}

