#include "TutorialGame.h"
#include "../CSC8503Common/GameWorld.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Common/TextureLoader.h"
#include "../CSC8503Common/Component.h"
#include "../CSC8503Common/Script.h"
#include "../CSC8503Common/offForward.h"

#include "../CSC8503Common/cubeDebuff.h"
#include "../CSC8503Common/TestBuff.h"
#include "../CSC8503Common/SpeedBoost.h"
#include "../CSC8503Common/Homing.h"
#include "../CSC8503Common/CurveBall.h"
#include "../CSC8503Common/sizeChange.h"

#include "../CSC8503Common/PositionConstraint.h"

#include "OBJ_Loader.h"

#include "SpherePhysicsComponent.h"
#include "BoxPhysicsComponent.h"
#include "TriangleMeshPhysicsComponent.h"

#include "PhysxController.h"
#include "WinningTriggerPlane.h"

#include <functional>

#include <stdlib.h>

using namespace NCL;
using namespace CSC8503;

TutorialGame::TutorialGame()	{
	srand(time(NULL));

	numberOfLevels = 4;
	for (int i = 0; i < numberOfLevels; i++)
	{
		worlds.push_back(new GameWorld());

		if (i != numberOfLevels - 1)
			PhysxController::getInstance().addNewScene();
	}

	score[0] = 0;
	score[1] = 0;
	score[2] = 0;
	score[3] = 0;

	winner = -1;
	draw = false;

	gameFinished = false;

	currentPlayerCount = 1;

	currentWorld = 0;
	renderer = new GameTechRenderer(*worlds[currentWorld]);
	
	UIworld = new GameWorld();
	UIrenderer = new GameTechRenderer(*UIworld);

	inSelectionMode = false;

	switchingLevels = false;

	Ball = nullptr;
	playerConnected = false;

	powerUpTxtLength = 5;
	powerUpTxtTimer = powerUpTxtLength;

	isNetworkedGame = false;
	isServer = false;
#ifdef WIN32
	Debug::SetRenderer(renderer);
#else 
	//PS4 code
#endif

	InitialiseAssets();
	StartGame();
}

void TutorialGame::InitialiseAssets() {

	auto loadFunc = [](const string& name, OGLMesh** into) {
		*into = new OGLMesh(name);
		(*into)->SetPrimitiveType(GeometryPrimitive::Triangles);
		(*into)->UploadToGPU();
	};

	loadFunc("cube.msh"		 , &cubeMesh);

	basicShader = new OGLShader("GameTechVert.glsl", "GameTechFrag.glsl");

	UIShader = new OGLShader("GameUIVert.glsl", "GameUIFrag.glsl");

	PlaySound(TEXT("BGM.wav"), NULL, SND_LOOP | SND_FILENAME | SND_ASYNC);

	LoadColladaRenderObjects();
}

GameObject* TutorialGame::AddStarToWorld(Vector3 position, int worldIndex, int ID)
{
	std::vector<GameObject*> resultList;
	std::vector<RenderObject*> renderList = powerUpStar->GetAllMesh();

	for (RenderObject* tempRender : renderList)
	{
		Star* star = new Star();

		//build render object
		RenderObject* newRender = new RenderObject(tempRender);
		Vector3 size = Vector3(10, 10, 10);
		star->GetTransform().SetWorldScale(size);

		star->GetTransform().SetWorldPosition(position);

		newRender->SetParentTransform(&star->GetTransform());
		star->SetRenderObject(newRender);

		//build physics volume
		std::vector<PxVec3> verts;
		std::vector<PxU32> tris;
		Matrix4 tempScale = Matrix4::Scale(size);

		for (Vector3 vert : newRender->GetMesh()->GetPositionData())
		{
			vert = tempScale * vert;
			verts.push_back(PxVec3(vert.x, vert.y, vert.z));
		}
		for (unsigned int index : newRender->GetMesh()->GetIndexData())		tris.push_back(index);
		

		Quaternion rotate = Quaternion(Matrix4::Rotation(-90, Vector3(1, 0, 0)));

		PxMaterial* mMaterial = PhysxController::getInstance().Physics()->createMaterial(0.99f, 0.99f, 0.5f);
		SpherePhysicsComponent* sphere = new SpherePhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z), PxQuat(rotate.x, rotate.y, rotate.z, rotate.w)), star, 5, 0.1, mMaterial, worldIndex);
		sphere->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		//PhysxController::getInstance().setupFiltering(sphere->getActor(), FilterGroup::eSTAR, FilterGroup::ePLAYER);

		star->addComponent(sphere);
		star->setPhysxComponent(sphere);
		sphere->setAsTrigger();

		star->setTutorialGame(this);

		star->SetNetworkObject(new NetworkObject(*star, ID));
		
		star->setGameWorld(worlds[worldIndex]);

		worlds[worldIndex]->starList.push_back(star);

		resultList.push_back(star);
		worlds[worldIndex]->AddGameObject(star);
	}

	return resultList[0];
}

TutorialGame::~TutorialGame()	{
	delete cubeMesh;
	delete basicShader;
	delete Ball;
	delete renderer;
	//delete world;

	for (int i = 0; i < worlds.size(); i++) 
	{
		delete worlds[i];
	}
}

void TutorialGame::StartGame()
{
	InitCamera();

	for (int i = 0; i < numberOfLevels; i++) 
	{
		InitWorld(i);
	}
	PhysxController::getInstance().setActiveScene(currentWorld);

	//InitWorld(0);

	InitUIWorld();

	std::vector < GameObject* >::const_iterator first;
	std::vector < GameObject* >::const_iterator last;

	//world->GetObjectIterators(first, last);

	worlds[currentWorld]->GetObjectIterators(first, last);

	int counter = 0;

	for (auto i = first; i != last; ++i) 
	{
		if (!(*i)->GetNetworkObject())
			(*i)->SetNetworkObject(new NetworkObject(*(*i), counter));
		counter++;
	}
}

void TutorialGame::InitCamera() {
	worlds[currentWorld]->GetMainCamera()->SetNearPlane(0.5f);
	worlds[currentWorld]->GetMainCamera()->SetFarPlane(500.0f);
	worlds[currentWorld]->GetMainCamera()->SetPitch(-15.0f);
	worlds[currentWorld]->GetMainCamera()->SetYaw(315.0f);
	worlds[currentWorld]->GetMainCamera()->SetPosition(Vector3(-60, 40, 60));
}

void TutorialGame::InitWorld(int worldIndex) {

	PhysxController::getInstance().setActiveScene(worldIndex);
	// The player to act as the server
	//AddPlayerToWorld(Vector3(0, 1, 0), 1);
	if (worldIndex == 0) 
	{
		int starCount = 0;

		AddStarToWorld(Vector3(-0.4, 0.15, 1), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(-0.1, 0.15, 1), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(0.1, 0.15, 1), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(0.4, 0.15, 1), worldIndex, 1000 + starCount);
		starCount++;

		AddSomeObject(level1, Vector3(  0,   0,    0),	worldIndex,		Vector3( 1,  1,  1),		Quaternion(Matrix4::Rotation( 00, Vector3(1, 0, 0))),		"map");
		WinningTriggerPlane* wPlane = new WinningTriggerPlane(PxTransform(PxVec3(-2.7,-0.3, 1.5)), 0.4, 0.2, 0.4, worldIndex, this);
		worlds[worldIndex]->AddGameObject(wPlane);
	}
	else if (worldIndex == 1)
	{
		int starCount = 0;

		AddStarToWorld(Vector3(-2, -0.9, 3), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(-2, -0.9, 3.3), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(-2, -0.9, 3.6), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(-2, -0.9, 3.9), worldIndex, 1000 + starCount);
		starCount++;

		WinningTriggerPlane* wPlane = new WinningTriggerPlane(PxTransform(PxVec3(0, -2.5, 3.1)), 0.4, 0.2, 0.4, worldIndex, this);
		worlds[worldIndex]->AddGameObject(wPlane);

		AddSomeObject(level2, Vector3(0, 0, 0), worldIndex, Vector3(1, 1, 1), Quaternion(Matrix4::Rotation(00, Vector3(1, 0, 0))), "map");
		// WinningTriggerPlane* wPlane = new WinningTriggerPlane(PxTransform(PxVec3(0, -5, 0)), 30, 2, 30, worldIndex, this);
		// worlds[worldIndex]->AddGameObject(wPlane);
	}
	else if (worldIndex == 2)
	{
		int starCount = 0;

		AddStarToWorld(Vector3(-0.5, 0.05, 2.5), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(-0.2, 0.05, 2.5), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(0, 0.05, 2.5), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(0.3, 0.05, 2.5), worldIndex, 1000 + starCount);
		starCount++;
		
		AddStarToWorld(Vector3(5.3, 0.05, 2.5), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(5.0, 0.05, 2.5), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(4.8, 0.05, 2.5), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(4.5, 0.05, 2.5), worldIndex, 1000 + starCount);
		starCount++;

		AddStarToWorld(Vector3(-3.5, 0.05, 1), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(-3.2, 0.05, 1), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(-3, 0.05, 1), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(-2.7, 0.05, 1), worldIndex, 1000 + starCount);
		starCount++;

		AddSomeObject(level3, Vector3(0, 0, 0), worldIndex, Vector3(1, 1, 1), Quaternion(Matrix4::Rotation(00, Vector3(1, 0, 0))), "map");

		WinningTriggerPlane* wPlane = new WinningTriggerPlane(PxTransform(PxVec3(-0.1, -0.5, 4.55)), 0.5, 0.2, 0.5, worldIndex, this);
		worlds[worldIndex]->AddGameObject(wPlane);
	}
	else if (worldIndex == 3)
	{
		int starCount = 0;

		AddStarToWorld(Vector3(-1.6, 0.10, 3), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(-1.9, 0.10, 3), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(-2.1, 0.10, 3), worldIndex, 1000 + starCount);
		starCount++;
		AddStarToWorld(Vector3(-2.4, 0.10, 3), worldIndex, 1000 + starCount);
		starCount++;

		AddSomeObject(level4, Vector3(0, 0, 0), worldIndex, Vector3(1, 1, 1), Quaternion(Matrix4::Rotation(00, Vector3(1, 0, 0))), "map");
		WinningTriggerPlane* wPlane = new WinningTriggerPlane(PxTransform(PxVec3(0, -0.5, 9.15)), 0.5, 0.2, 0.5, worldIndex, this);
		worlds[worldIndex]->AddGameObject(wPlane);
	}
}

void TutorialGame::LoadColladaRenderObjects() {

	auto mshLoadFunc = [](MeshSceneNode** sceneNode, const char* meshName, const char* textureName, OGLShader* shader) {
		(*sceneNode) = new MeshSceneNode();

		OGLMesh* tempMesh = new OGLMesh(meshName);

		OGLTexture* tempTexture = (OGLTexture*)TextureLoader::LoadAPITexture(textureName);

		vector<unsigned int> indices;
		for (int i = 0; i < tempMesh->GetPositionData().size(); i++)
		{
			indices.push_back(i);
		}
		
		tempMesh->SetVertexIndices(indices);

		tempMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
		tempMesh->UploadToGPU();

		RenderObject* tempMe = new RenderObject(tempMesh, tempTexture, shader);
		(*sceneNode)->AddMesh(tempMe);
	};
	auto colladaLoadFunc = [](MeshSceneNode** sceneNode, const char* meshName, const char* textureName, OGLShader* shader) {
		(*sceneNode) = new MeshSceneNode();

		ColladaBase* tempMesh = new ColladaBase(meshName);

		int meshSize = tempMesh->GetNumMeshes();

		OGLTexture* tempTexture = nullptr;

		tempTexture = (OGLTexture*)TextureLoader::LoadAPITexture(textureName);

		for (EnjoyMesh tempIn : tempMesh->GetMeshes()) {
			float tempF[16];
			for (size_t i = 0; i < 16; i++) tempF[i] = tempIn.transform[i];
			Matrix4 tempMat(tempF);
			tempMat.Transpose();

			//build new array
			OGLMesh* tempOGLMesh = new OGLMesh();

			vector<Vector3> vertics;
			vector<Vector3> normals;
			vector<Vector2> texCoords;
			vector<unsigned int> indices;
			

			//transform information to vector format
			for (int i = tempIn.indices[0]; i < tempIn.indices.size(); i++)
			{
				Matrix4 temp;
				Vector4 tempVec(tempIn.vertices[i].x, tempIn.vertices[i].y, tempIn.vertices[i].z, 1);

				tempVec = tempMat * tempVec;

				vertics.push_back(Vector3(tempVec) * 0.01);
				normals.push_back(Vector3(tempIn.normals[i].x, tempIn.normals[i].y, tempIn.normals[i].z));

				texCoords.push_back(Vector2(tempIn.texcoords[i].x, tempIn.texcoords[i].y));

				indices.push_back(i);
			}

			//set mesh information
			tempOGLMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
			tempOGLMesh->SetVertexPositions(vertics);
			tempOGLMesh->SetVertexNormals(normals);

			tempOGLMesh->SetVertexTextureCoords(texCoords);

			tempOGLMesh->SetVertexIndices(indices);
			tempOGLMesh->UploadToGPU();

			RenderObject* tempMe = new RenderObject(tempOGLMesh, tempTexture, shader);

			(*sceneNode)->AddMesh(tempMe);
		}
	};
	auto objLoadFunc = [](MeshSceneNode** sceneNode, const char* meshName, const char* textureName, OGLShader* shader) {
		(*sceneNode) = new MeshSceneNode();

		objl::Loader loader;
		bool loadout = loader.LoadFile(meshName);
		if (!loadout) return;

		OGLTexture* tempTexture = (OGLTexture*)TextureLoader::LoadAPITexture(textureName);

		for (objl::Mesh tempOriMesh : loader.LoadedMeshes)
		{
			OGLMesh* tempMesh = new OGLMesh();

			vector<Vector3> verts;
			vector<Vector3> normals;
			vector<Vector2> texCoords;
			vector<unsigned int> indices;

			for (int i = 0; i < tempOriMesh.Vertices.size(); i++) {

				verts.push_back(Vector3(tempOriMesh.Vertices[i].Position.X, tempOriMesh.Vertices[i].Position.Y, tempOriMesh.Vertices[i].Position.Z));
				normals.push_back(Vector3(tempOriMesh.Vertices[i].Normal.X, tempOriMesh.Vertices[i].Normal.Y, tempOriMesh.Vertices[i].Normal.Z));
				texCoords.push_back(Vector2(tempOriMesh.Vertices[i].TextureCoordinate.X, tempOriMesh.Vertices[i].TextureCoordinate.Y));
				indices.push_back(tempOriMesh.Indices[i]);
			}

			tempMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
			tempMesh->SetVertexPositions(verts);
			tempMesh->SetVertexNormals(normals);
			tempMesh->SetVertexTextureCoords(texCoords);
			tempMesh->SetVertexIndices(indices);
			tempMesh->UploadToGPU();

			RenderObject* tempMe = new RenderObject(tempMesh, tempTexture, shader);

			(*sceneNode)->AddMesh(tempMe);

		}
	};
	auto colladaLoadFuncMulTex = [](MeshSceneNode** sceneNode, const char* meshName, vector<char*> textureName, OGLShader* shader) {
		(*sceneNode) = new MeshSceneNode();

		ColladaBase* tempMesh = new ColladaBase(meshName);

		int meshSize = tempMesh->GetNumMeshes();

		OGLTexture* defaultTex = (OGLTexture*)TextureLoader::LoadAPITexture("checkerboard.png");
		std::vector<OGLTexture*> tempTexture;
		for (size_t i = 0; i < meshSize; i++) tempTexture.push_back(defaultTex);
		for (size_t i = 0; i < textureName.size(); i++)
		{
			OGLTexture* tempTex = (OGLTexture*)TextureLoader::LoadAPITexture((textureName[i]));
			tempTexture[i] = tempTex;
		}

		std::vector<EnjoyMesh> meshList = tempMesh->GetMeshes();
		for (int j = 0; j < meshList.size(); j++)
		{
			float tempF[16];
			for (size_t i = 0; i < 16; i++) tempF[i] = meshList[j].transform[i];
			Matrix4 tempMat(tempF);

			tempMat.Transpose();

			//tempMat = Matrix4::Scale(Vector3(0.01,0.01,0.01)) * tempMat;

			//build new array
			OGLMesh* tempOGLMesh = new OGLMesh();
			vector<Vector3> vertics;
			vector<Vector3> normals;
			vector<Vector2> texCoords;
			vector<unsigned int> indices;


			//transform information to vector format
			for (int i = meshList[j].indices[0]; i < meshList[j].indices.size(); i++)
			{
				Matrix4 temp;
				Vector4 tempVec(meshList[j].vertices[i].x, meshList[j].vertices[i].y, meshList[j].vertices[i].z, 1);

				tempVec = tempMat * tempVec;

				vertics.push_back(Vector3(tempVec) * 0.01);
				normals.push_back(Vector3(meshList[j].normals[i].x, meshList[j].normals[i].y, meshList[j].normals[i].z));
				texCoords.push_back(Vector2(meshList[j].texcoords[i].x, meshList[j].texcoords[i].y));
				indices.push_back(i);
			}

			//set mesh information
			tempOGLMesh->SetPrimitiveType(GeometryPrimitive::Triangles);
			tempOGLMesh->SetVertexPositions(vertics);
			tempOGLMesh->SetVertexNormals(normals);
			tempOGLMesh->SetVertexTextureCoords(texCoords);
			tempOGLMesh->SetVertexIndices(indices);
			tempOGLMesh->UploadToGPU();

			RenderObject* tempMe = new RenderObject(tempOGLMesh, tempTexture[j], shader);

			(*sceneNode)->AddMesh(tempMe);
		}
	};

	//				target					mesh				texture						shader
	colladaLoadFunc(&gameMapOrigin,		"TestLevel.dae",	"tex_MinigolfPack.png",		basicShader);
	colladaLoadFunc(&gameMapExplode,	"Level3.dae",		"tex_MinigolfPack.png",		basicShader);
	colladaLoadFunc(&treeFormRhino,		"treeR.dae",		"tex_MinigolfPack.png",		basicShader);
	colladaLoadFunc(&treeFromBlender,	"enjoyTree.dae",	"tex_tree.png",				basicShader);
	colladaLoadFunc(&powerUpStar,		"Star.dae",			"star.png",					basicShader);

	colladaLoadFunc(&level1, "Level1.dae", "tex_MinigolfPack.png", basicShader);
	colladaLoadFunc(&level2, "Level2.dae", "tex_MinigolfPack.png", basicShader);
	colladaLoadFunc(&level3, "Level3.dae", "tex_MinigolfPack.png", basicShader);
	colladaLoadFunc(&level4, "Level4.dae", "tex_MinigolfPack.png", basicShader);

	/*for (int i = 0; i < numberOfLevels; i++) 
	{
		MeshSceneNode* node = new MeshSceneNode();
		levelMeshes.push_back(node);

		char name[11] = "Level#.dae";

 		name[5] = '0' + (i + 1);

		colladaLoadFunc(&node, name, "tex_MinigolfPack.png", basicShader);
	}*/

	objLoadFunc(&playerTemp1, "Assets/Ball6.obj", "tex_MinigolfPack.png", basicShader);
	objLoadFunc(&playerTemp2, "Assets/Ball9.obj", "tex_MinigolfPack.png", basicShader);
	objLoadFunc(&playerTemp3, "Assets/Ball10.obj", "tex_MinigolfPack.png", basicShader);
	objLoadFunc(&playerTemp0, "Assets/Ball3.obj", "tex_MinigolfPack.png", basicShader);

	std::vector<char*> temp;
	temp.push_back("wood.png");
	temp.push_back("greenglass.jpg");
	colladaLoadFuncMulTex(&treeWithMultiTex,"tree.dae",		temp,						basicShader);
}

vector<GameObject*> TutorialGame::	AddSomeObject(MeshSceneNode* sceneNode, const Vector3& position, const int worldIndex, const Vector3& size, Quaternion rotate, std::string objectName)
{
	std::vector<GameObject*> resultList;
	std::vector<RenderObject*> renderList = sceneNode->GetAllMesh();

	for (RenderObject* tempRender : renderList)
	{

		//build object list
		GameObject* tempObject = new GameObject(objectName);

		//build rander object
		RenderObject* newRender = new RenderObject(tempRender);
		
		tempObject->GetTransform().SetWorldScale(size);

		tempObject->GetTransform().SetWorldPosition(position + Vector3(150, 150, 150));
		
		newRender->SetParentTransform(&tempObject->GetTransform());
		tempObject->SetRenderObject(newRender);

		//build physics volume
		std::vector<PxVec3> verts;
		std::vector<PxU32> tris;
		Matrix4 tempScale = Matrix4::Scale(size);

		for (Vector3 vert : newRender->GetMesh()->GetPositionData()) 
		{
			vert = tempScale * vert;
			verts.push_back(PxVec3(vert.x, vert.y, vert.z));
		}
		for(unsigned int index : newRender->GetMesh()->GetIndexData())		tris.push_back(index);
		PxMaterial* mMaterial = PhysxController::getInstance().Physics()->createMaterial(0.99f, 0.99f, 0.5f);

		TriangleMeshPhysicsComponent* physicsC = new TriangleMeshPhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z), PxQuat(rotate.x, rotate.y, rotate.z, rotate.w)), tempObject, 10000, verts, tris, mMaterial, worldIndex);

		PhysxController::getInstance().setupFiltering(physicsC->getActor(), FilterGroup::eLEVEL, FilterGroup::ePLAYER);
		tempObject->addComponent(physicsC);

		resultList.push_back(tempObject);
		worlds[worldIndex]->AddGameObject(tempObject);
	}
	return resultList;
}

Player* TutorialGame::			AddSphereObjectToWorld(MeshSceneNode* sceneNode, const Vector3& position, int scene, int playerID, const Vector3& size, std::string objectName)
{
	Player* BallTemp = new Player(playerID);

	BallTemp->setLayer(5);
	BallTemp->isCurrentPlayer = false;

	//build render object
	std::vector<RenderObject*> renderList = sceneNode->GetAllMesh();
	OGLMesh* objOGL = new OGLMesh(renderList[0]->GetMesh());
	RenderObject* newRender = new RenderObject(renderList[0]);

	BallTemp->GetTransform().SetWorldScale(size);
	BallTemp->GetTransform().SetWorldPosition(position);
	newRender->SetParentTransform(&BallTemp->GetTransform());
	BallTemp->SetRenderObject(newRender);
	/////////////////////
	BallTemp->SetCubeMesh(cubeMesh);
	/////////////////////
	BallTemp->SetPlayerMesh(objOGL);

	//renderer->SetBallObject(BallTemp);

	//physics component
	if (isServer)
	{
		SpherePhysicsComponent* sphere = nullptr;
		PxMaterial* mMaterial = PhysxController::getInstance().Physics()->createMaterial(0.99f, 0.99f, 1);
		sphere = new SpherePhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), BallTemp, 10, 0.05, mMaterial, scene);
		BallTemp->addComponent(sphere);
		sphere->setLinearDamping(0.8);
		sphere->setAngularDamping(2);
	}

	BallTemp->SetNetworkObject(new NetworkObject(*BallTemp, playerID));

	worlds[currentWorld]->AddGameObject(BallTemp);

	return BallTemp;
}

Player* TutorialGame::AddPlayerObjectToWorld(MeshSceneNode* sceneNode, const Vector3& position, int scene, int playerID, const Vector3& size, std::string objectName)
{
	int i = 0;
	//real code
	Ball = new Player(playerID);
	Ball->setCamera(worlds[currentWorld]->GetMainCamera());

	playerConnected = true;

	//build render object
	std::vector<RenderObject*> renderList = sceneNode->GetAllMesh();
	OGLMesh* objOGL = new OGLMesh(renderList[0]->GetMesh());
	RenderObject* newRender = new RenderObject(renderList[0]);

	Ball->GetTransform().SetWorldScale(size);
	Ball->GetTransform().SetWorldPosition(position);
	newRender->SetParentTransform(&Ball->GetTransform());
	Ball->SetRenderObject(newRender);
	/////////////////////
	Ball->SetCubeMesh(cubeMesh);
	/////////////////////
	Ball->SetPlayerMesh(objOGL);

	renderer->SetBallObject(Ball);

	//physics component
	if (isServer)
	{
		SpherePhysicsComponent* sphere = nullptr;
		PxMaterial* mMaterial = PhysxController::getInstance().Physics()->createMaterial(0.99f, 0.99f, 1);
		sphere = new SpherePhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), Ball, 10, 0.05, mMaterial, scene);
		Ball->addComponent(sphere);
		sphere->setLinearDamping(0.8);
		sphere->setAngularDamping(2);
	}

	Ball->SetNetworkObject(new NetworkObject(*Ball, playerID));
	Ball->setWorldNumber(scene);
	//Ball->addComponent(new CurveBall());

	worlds[currentWorld]->AddGameObject(Ball);

	return Ball;
}

void TutorialGame::changeLevel()
{
	if (gameFinished)
		return;

	switchingLevels = true;

	if (currentWorld >= 0)
	{
		gameFinished = true;
		winner = 0;

		for (int i = 1; i < 4; i++)
		{
			if ((score[i] < score[winner]) && (score[i] > 0))
				winner = i;
		}

		int count = 0;
		for (int i = 0; i < 4; i++)
		{
			if (score[i] == score[winner])
				count++;
		}

		if (count > 1)
			draw = true;
		
		return;
	}

	currentWorld++;
	otherplayers.clear();

	if (isServer)
	{

		PhysxController::getInstance().setActiveScene(currentWorld);

		int shotsSoFar = Ball->getComponent<ShotTracker*>("ShotTracker")->getShots();

		AddPlayerObjectToWorld(getPlayerMesh(0), Vector3(-0.4, 0.1, -0.9), currentWorld, 0, Vector3(1, 1, 1), "player" + 0);

		Ball->getComponent<ShotTracker*>("ShotTracker")->setShots(shotsSoFar);

		for (int i = 1; i < serverPlayers.size(); i++)
		{
			Vector3 pos;
			if (i == 1) {
				pos = Vector3(-0.2, 0.1, -0.9);
			}
			else if (i == 2) {
				pos = Vector3(0.2, 0.1, -0.9);
			}
			else if (i == 3) {
				pos = Vector3(0.4, 0.1, -0.9);
			}

			int shots = serverPlayers[i]->getComponent<ShotTracker*>("ShotTracker")->getShots();

			Player* p = AddSphereObjectToWorld(getPlayerMesh(i), pos, currentWorld, i, Vector3(1, 1, 1), "player" + i);

			p->getComponent<ShotTracker*>("ShotTracker")->setShots(shotsSoFar);

			if (isServer)
				p->isServer = true;

			serverPlayers[i] = p;
			otherplayers.push_back(serverPlayers[i]);
		}

		renderer->SetWorld(*worlds[currentWorld]);
		InitCamera();

		renderer->SetBallObject(Ball);

		Ball->isCurrentPlayer = true;

		otherplayers.push_back(Ball);

		if (isServer)
			Ball->isServer = true;

		serverPlayers[0] = Ball;
	}
	else
	{

		for (int i = 0; i < serverPlayers.size(); i++)
		{
			Vector3 pos;
			if (i == 0) {
				pos = Vector3(-0.4, 0.1, -0.9);
			}
			else if (i == 1) {
				pos = Vector3(-0.2, 0.1, -0.9);
			}
			else if (i == 2) {
				pos = Vector3(0.2, 0.1, -0.9);
			}
			else if (i == 3) {
				pos = Vector3(0.4, 0.1, -0.9);
			}

			Player* p = nullptr;

			if (i == Ball->getID())
			{
				p = AddPlayerObjectToWorld(getPlayerMesh(i), pos, currentWorld, i, Vector3(1, 1, 1), "player" + i);
				p->isCurrentPlayer = true;
			}
			else
			{
				p = AddSphereObjectToWorld(getPlayerMesh(i), pos, currentWorld, i, Vector3(1, 1, 1), "player" + i);
			}
				

			if (p)
				serverPlayers[i] = p;

			otherplayers.push_back(serverPlayers[i]);
		}

		renderer->SetWorld(*worlds[currentWorld]);
		InitCamera();

		renderer->SetBallObject(Ball);
	}
}

MeshSceneNode* TutorialGame::getPlayerMesh(int ID) {
	if (ID == 0) {
		return playerTemp0;
	} else if (ID == 1) {
		return playerTemp1;
	}
	else if (ID == 2) {
		return playerTemp2;
	}
	else if (ID == 3) {
		return playerTemp3;
	}
}

void TutorialGame::UpdateGame(float dt) {

#ifdef _ORBIS
	//PS4 code
#else 
	//update inter UI
	if (UIworld->GetUIactive() == false)
	{
		UpdateUIWorld(dt);
		if (UIworld->GetUIactive() == false)return;
	}

	//update Render
	UpdateInGame();
	UpdateKeys();

	SelectObject();
	if (displayFPS) {
		renderer->DrawString(std::to_string((int)((1 / dt))) + " FPS", Vector2(WIDTH - 200, HEIGHT - 100));
	}

	if (paused) {
		if(isNetworkedGame)
			dt = 0;
		displayPauseMenu();
	}

	if (gameFinished)
		displayWinner(dt);
	else
		displayScoreBoard(dt);

	if (powerUpName.size() > 0)
		displayPowerUpText(dt);

	if (!gameFinished)
		worlds[currentWorld]->UpdateWorld(dt);

	renderer->Update(dt);
	SelectObject();

	Debug::FlushRenderables();
	renderer->Render();

	//update NetWork
	UpdateNetworkPostion(Ball);
#endif
}

void TutorialGame::displayPauseMenu() {
	renderer->DrawString("Quit?", Vector2(WIDTH / 2 - 50, HEIGHT/2));
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::RETURN)) {
		ifQuitGame = true;
	}
}

void TutorialGame::displayPowerUpText(float dt)
{
#ifdef WIN32
	renderer->DrawString(powerUpName, Vector2(500, 600));
#else 
#endif
	
	powerUpTxtTimer -= dt;

	if (powerUpTxtTimer <= 0) 
	{
		powerUpName.clear();
		powerUpTxtTimer = powerUpTxtLength;
	}
}

void TutorialGame::displayWinner(float dt) 
{
	int startYPos = 400;
	int startXPos = 400;

	if (!Ball)
		return;

	if (draw && (score[winner] == score[Ball->getID()]))
	{
		renderer->DrawString("!! DRAW !!", Vector2(startXPos, startYPos));
	}
	else if (winner == Ball->getID())
	{
		renderer->DrawString("!! WINNER WINNER CHICKEN DINNER !!", Vector2(startXPos - 300, startYPos));
	}
	else 
	{
		renderer->DrawString("!! YOU LOSE !!", Vector2(startXPos, startYPos));
	}

	renderer->DrawString("FINAL SCORES: ", Vector2(startXPos + 10, startYPos - 30));

	renderer->DrawString("Player1: " + std::to_string(score[0]), Vector2(startXPos + 40, startYPos - 60));

	renderer->DrawString("Player2: " + std::to_string(score[1]), Vector2(startXPos + 40, startYPos - 90));

	renderer->DrawString("Player3: " + std::to_string(score[2]), Vector2(startXPos + 40, startYPos - 120));

	renderer->DrawString("Player4: " + std::to_string(score[3]), Vector2(startXPos + 40, startYPos - 150));
}

void TutorialGame::displayScoreBoard(float dt)
{
#ifdef WIN32

	int startYPos = 650;
	int startXPos = 900;

	if (isServer) 
	{
		int i = 0;
		for (auto it = serverPlayers.begin(); it != serverPlayers.end(); it++) {
			if (it->second == NULL) {
				continue;
			}

			score[i] = it->second->getComponent<ShotTracker*>("ShotTracker")->getShots();
			i++;
		}
	}

	renderer->DrawString("SHOTS TAKEN:", Vector2(startXPos, startYPos));

	renderer->DrawString("Player1: " + std::to_string(score[0]), Vector2(startXPos, startYPos - 30));

	renderer->DrawString("Player2: " + std::to_string(score[1]), Vector2(startXPos, startYPos - 60));
	
	renderer->DrawString("Player3: " + std::to_string(score[2]), Vector2(startXPos, startYPos - 90));

	renderer->DrawString("Player4: " + std::to_string(score[3]), Vector2(startXPos, startYPos - 120));
	
#else 
#endif
}

void TutorialGame::UpdateKeys() {
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::F1)) {
		InitWorld(0); //We can reset the simulation at any time with F1
	}

	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::F2)) {
		UIworld->SetUIactive(false);
		//de something else
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::F3)) {
		displayFPS = !displayFPS;
	}

	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::ESCAPE)) {
		paused = !paused;
	}
}

bool TutorialGame::SelectObject() {
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::Q)) {
		inSelectionMode = !inSelectionMode;
		if (inSelectionMode) {
			Window::GetWindow()->ShowOSPointer(true);
			Window::GetWindow()->LockMouseToWindow(false);
		}
		else {
			Window::GetWindow()->ShowOSPointer(false);
			Window::GetWindow()->LockMouseToWindow(true);
		}
	}
	return false;
}

//following is UIfunction

void TutorialGame::UpdateInGame() {
#ifdef WIN32
	renderer->DrawString("Your point : XXXXXX ", Vector2(10, 0));
#else 
	//PS4 code
#endif

}

void TutorialGame::InitUIWorld()
{
	//initialize UIBar
	interBar1 = new UIBar("Begin game");
	interBar2 = new UIBar("NoFunctionNow");
	interBar3 = new UIBar("Quit game");

	gameMode1 = new UIBar("NormalMode");
	gameMode2 = new UIBar("Create Server");
	gameMode3 = new UIBar("Create Client");
	gameMode4 = new UIBar("Back to menu");

	//link function to UIBar
	auto quitgame = [this]() {ifQuitGame = true; };
	interBar3->funL = quitgame;


	auto intogame = [this]() {
		isNetworkedGame = true;
		solo = true;
		isServer = true;
		UIworld->SetUIactive(true); 
		renderer->SetGameStarted();
	};
	gameMode1->funL = intogame;

	auto servergame = [this]() { 
		isNetworkedGame = true;
		solo = false;
		isServer = true;
		UIworld->SetUIactive(true);
		renderer->SetGameStarted();
	};
	gameMode2->funL = servergame;

	auto clientgame = [this]() { 
		isNetworkedGame = true;
		solo = false;
		isServer = false;
		UIworld->SetUIactive(true);
		renderer->SetGameStarted();
	};
	gameMode3->funL = clientgame;

	//initialize UIState
	interFace = new UIState();
	interFace->AddBar(interBar1);
	interFace->AddBar(interBar2);
	interFace->AddBar(interBar3);
	interFace->SetCurrentBar(interFace->GetUIList().front());

	gameMode = new UIState();
	gameMode->AddBar(gameMode1);
	gameMode->AddBar(gameMode2);
	gameMode->AddBar(gameMode3);
	gameMode->AddBar(gameMode4);
	gameMode->SetCurrentBar(gameMode->GetUIList().front());


	//link layout relationships
	gameMode4->subState = interFace;
	interBar1->subState = gameMode;

	//initialize UImachine
	UIMachine = new UIPushDownMachine();
	UIMachine->SetVertical(50,600);
	UIMachine->AddState(interFace);
	UIMachine->AddState(gameMode);
	UIMachine->SetCurrentState(UIMachine->GetStateList().front());

	//initiate UIworld
	UIworld->ClearAndErase();
	UIworld->SetUIactive(false);

}

void TutorialGame::UpdateUIWorld(float dt)
{
#ifdef WIN32
	UIrenderer->DrawString("W S choose mode, D into select", Vector2(50, 0), Vector4(0, 1, 0, 0));
	UIMachine->LoadUIState(UIrenderer);
	UpdateUIKeyWords(UIMachine);
	UIrenderer->Update(dt);
	UIrenderer->Render();
#else 
	//PS4 code
#endif

}

void TutorialGame::UpdateUIKeyWords(UIPushDownMachine* UIMachine)
{
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::W)) {
		UIMachine->UpBar();
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::S)) {
		UIMachine->DownBar();
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::D)) {
		UIMachine->IntoBar();
	}
}