#pragma once
#include "GameTechRenderer.h"
#include "../CSC8503Common/PhysicsSystem.h"
#include "Player.h"
#include <stdlib.h>
#include <string> 
#include <iostream>
#include <fstream>
#include "../CSC8503Common/ColladaBase.h"
#include "PhysxController.h"
#include "MeshSceneNode.h"
#include "Star.h"
#include "../CSC8503Common/UIPushDownMachine.h"
#include "../CSC8503Common/ShotTracker.h"

namespace NCL {
	namespace CSC8503 {
		class TutorialGame		{
		public:
			TutorialGame();
			~TutorialGame();

			virtual void UpdateGame(float dt);

			void displayPauseMenu();
			bool IfQuitGame() { return ifQuitGame; }

			void setPowerUpName(string name) { powerUpName = name; };

			OGLMesh* cubeMesh = nullptr;
			MeshSceneNode* getPlayerMesh(int ID = 0);

			// Public variables due to time constraints
			int currentWorld;
			int currentPlayerCount;

			bool getIsServer() { return isServer; };
			bool isPaused() { return paused; }

			bool hasPlayer() { return playerConnected; };

			void setSwitchingLevels() { switchingLevels = true; };

			Player* AddSphereObjectToWorld(MeshSceneNode* sceneNode, const Vector3& position, int scene, int playerID, const Vector3& size = Vector3(1, 1, 1), std::string objectName = "");
			Player* AddPlayerObjectToWorld(MeshSceneNode* sceneNode, const Vector3& position, int scene, int playerID, const Vector3& size = Vector3(1, 1, 1), std::string objectName = "");

			void changeLevel();
			const bool isSolo() { return solo; }

			void setScore(int id, int shots) { score[id] = shots; };
		protected:

			//check if you need show mouse on window
			bool SelectObject();

			Player* Ball;
			Player* playerTwo;

			bool switchingLevels;

			bool playerConnected;

			bool isNetworkedGame;
			bool solo;
			bool isServer;
			bool displayFPS = false;

			virtual void UpdateNetworkPostion(GameObject* obj) = 0;

			//initiate the game
			void InitialiseAssets();
			void InitCamera();
			void InitWorld(int worldIndex);
			void StartGame();
			void LoadColladaRenderObjects();
			//sub functions of initiate
			vector<GameObject*> AddSomeObject(MeshSceneNode* sceneNode, const Vector3& position, const int worldIndex, const Vector3& size = Vector3(1, 1, 1), Quaternion rotate = Quaternion(Matrix4::Rotation(0, Vector3(0, 0, 0))), std::string objectName = "");
			GameObject* AddStarToWorld(Vector3 position, int worldIndex, int ID);
			
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
			//GameWorld* world;


			// Testing multiple levels
			vector<GameWorld*> worlds;
			vector<MeshSceneNode*> levelMeshes;

			MeshSceneNode* level1;
			MeshSceneNode* level2;
			MeshSceneNode* level3;
			MeshSceneNode* level4;

			int numberOfLevels;

			bool inSelectionMode;
			OGLShader* basicShader = nullptr;

			float	forceMagnitude;

			void displayScoreBoard(float dt);
			int score[4];

			void displayPowerUpText(float dt);
			string powerUpName;
			float powerUpTxtLength;
			float powerUpTxtTimer;

			std::map<int, GameObject*> serverPlayers;
			
			OGLTexture* basicTex	= nullptr;
			OGLTexture* golfLevelTex = nullptr;

			//NavigationGrid grid;

			std::vector<GameObject*> otherplayers;

			//UI system, still fix , do not need check
			GameWorld* UIworld;
			GameTechRenderer* UIrenderer;

			UIPushDownMachine* UIMachine;
			UIState* interFace;
			UIState* gameMode;
			
			//buttons in interface
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
			bool paused = false;
			OGLShader* UIShader = nullptr;
		};
	}
}

