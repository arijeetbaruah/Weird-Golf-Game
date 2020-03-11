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

#include "../CSC8503Common/PositionConstraint.h"

#include "OBJ_Loader.h"

#include "SpherePhysicsComponent.h"
#include "BoxPhysicsComponent.h"
#include "TriangleMeshPhysicsComponent.h"

#include "PhysxController.h"

#include <functional>
using namespace NCL;
using namespace CSC8503;

TutorialGame::TutorialGame()	{
	world = new GameWorld();
	renderer = new GameTechRenderer(*world);

	UIworld = new GameWorld();
	UIrenderer = new GameTechRenderer(*UIworld);

	inSelectionMode = false;
	log = std::unique_ptr<Logger>(new Logger("Tutorial Game"));

	Ball = nullptr;

	powerUpTxtLength = 5;
	powerUpTxtTimer = powerUpTxtLength;

	isNetworkedGame = false;
	isServer = false;

	Debug::SetRenderer(renderer);

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

	LoadColladaRenderObjects();
}

GameObject* TutorialGame::AddStarToWorld(Vector3 position)
{
	std::vector<GameObject*> resultList;
	std::vector<RenderObject*> renderList = powerUpStar->GetAllMesh();

	for (RenderObject* tempRender : renderList)
	{
		Star* star = new Star();

		//build rander object
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

		for each (Vector3 vert in newRender->GetMesh()->GetPositionData())
		{
			vert = tempScale * vert;
			verts.push_back(PxVec3(vert.x, vert.y, vert.z));
		}
		for each (unsigned int index in newRender->GetMesh()->GetIndexData())		tris.push_back(index);
		PxMaterial* mMaterial = PhysxController::getInstance().Physics()->createMaterial(0.99f, 0.99f, 0.5f);

		Quaternion rotate = Quaternion(Matrix4::Rotation(-90, Vector3(1, 0, 0)));

		//TriangleMeshPhysicsComponent* physicsC = new TriangleMeshPhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z), PxQuat(rotate.x, rotate.y, rotate.z, rotate.w)), 1, verts, tris, mMaterial);
		//star->addComponent(physicsC);

		SpherePhysicsComponent* sphere = new SpherePhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z), PxQuat(rotate.x, rotate.y, rotate.z, rotate.w)), star, 5, 0.1, mMaterial);
		sphere->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		PhysxController::getInstance().setupFiltering(sphere->getActor(), FilterGroup::eSTAR, FilterGroup::ePLAYER);

		star->addComponent(sphere);

		star->setTutorialGame(this);
		
		star->setPhysxComponent(sphere);

		sphere->setAsTrigger();
		
		star->setGameWorld(world);

		resultList.push_back(star);
		world->AddGameObject(star);
	}

	return resultList[0];
}

TutorialGame::~TutorialGame()	{
	delete cubeMesh;
	delete basicShader;
	delete Ball;
	delete renderer;
	delete world;
}

void TutorialGame::StartGame()
{
	InitCamera();
	InitWorld();
	InitUIWorld();

	std::vector < GameObject* >::const_iterator first;
	std::vector < GameObject* >::const_iterator last;

	world->GetObjectIterators(first, last);

	int counter = 0;

	for (auto i = first; i != last; ++i) 
	{
		if (!(*i)->GetNetworkObject())
			(*i)->SetNetworkObject(new NetworkObject(*(*i), counter));
		counter++;
	}
}

void TutorialGame::InitCamera() {
	world->GetMainCamera()->SetNearPlane(0.5f);
	world->GetMainCamera()->SetFarPlane(500.0f);
	world->GetMainCamera()->SetPitch(-15.0f);
	world->GetMainCamera()->SetYaw(315.0f);
	world->GetMainCamera()->SetPosition(Vector3(-60, 40, 60));
}

void TutorialGame::InitWorld() {
	world->ClearAndErase();

	// The player to act as the server
	//AddPlayerToWorld(Vector3(0, 1, 0), 1);

	AddStarToWorld(Vector3(-0.4, 0.3, 1));
	AddStarToWorld(Vector3(-0.1, 0.3, 1));
	AddStarToWorld(Vector3(0.1, 0.3, 1));
	AddStarToWorld(Vector3(0.4, 0.3, 1));

	//			 RenderObject(must)	    Position(must)					scale					rotation													name
	AddSomeObject(gameMapOrigin,	Vector3(  0,   0,    0),		Vector3( 1,  1,  1),		Quaternion(Matrix4::Rotation( 00, Vector3(1, 0, 0))),		"map");
	AddSomeObject(gameMapExplode,	Vector3(  0, -0.5,   2),		Vector3( 1,  1,  1),		Quaternion(Matrix4::Rotation( 00, Vector3(1, 0, 0))),		"map");
	AddSomeObject(gameMapOrigin,	Vector3(  0, -1.5,   4),		Vector3( 1,  1,  1),		Quaternion(Matrix4::Rotation( 00, Vector3(1, 0, 0))),		"map");
	AddSomeObject(gameMapExplode,	Vector3(  0, -2.0,   6),		Vector3( 1,  1,  1),		Quaternion(Matrix4::Rotation( 00, Vector3(1, 0, 0))),		"map");
	//AddSomeObject(treeFormRhino,	Vector3(  0,    0, 0.5),		Vector3( 1,	 1,  1),		Quaternion(Matrix4::Rotation(-90, Vector3(1, 0, 0))),		"tree");
	//AddSomeObject(treeWithMultiTex,	Vector3(  0,    0,   0),		Vector3(10, 10, 10),		Quaternion(Matrix4::Rotation(-90, Vector3(1, 0, 0))),		"tree");
	//AddSomeObject(treeFromBlender,	Vector3(  0,	0,-0.3),		Vector3(10, 10, 10),		Quaternion(Matrix4::Rotation(-90, Vector3(1, 0, 0))),		"tree");
	//AddSomeObject(UIbar,			Vector3(0, 0, -0.3),			Vector3(0.1,0.1,0.1),		Quaternion(Matrix4::Rotation(00, Vector3(0, 0, 0))),		"");
	
	////						RenderObject(must)				   Position(must)			Scale				Name
	//otherplayers.push_back(AddPlayerObjectToWorld(playerTemp1, Vector3(-0.2, 0.1, -0.9), Vector3(1, 1, 1), "player2"));
	//otherplayers.push_back(AddPlayerObjectToWorld(playerTemp2, Vector3(0.2, 0.1, -0.9) , Vector3(1, 1, 1), "player3"));
	//otherplayers.push_back(AddPlayerObjectToWorld(playerTemp3, Vector3(0.4, 0.1, -0.9) , Vector3(1, 1, 1), "player4"));

	//// add the player controller
	//AddPlayerObjectToWorld(playerTemp0, Vector3(-0.4, 0.1, -0.9), Vector3(1, 1, 1), "player0");

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
	colladaLoadFunc(&gameMapExplode,	"TestLevel2.dae",	"tex_MinigolfPack.png",		basicShader);
	colladaLoadFunc(&treeFormRhino,		"treeR.dae",		"tex_MinigolfPack.png",		basicShader);
	colladaLoadFunc(&treeFromBlender,	"enjoyTree.dae",	"tex_tree.png",				basicShader);
	colladaLoadFunc(&powerUpStar,		"Star.dae",			"star.png",					basicShader);

	objLoadFunc    (&playerTemp1,		"Assets/Ball6.obj", "tex_MinigolfPack.png",		basicShader);
	objLoadFunc	   (&playerTemp2,		"Assets/Ball9.obj", "tex_MinigolfPack.png",		basicShader);
	objLoadFunc    (&playerTemp3,		"Assets/Ball10.obj", "tex_MinigolfPack.png",	basicShader);
	objLoadFunc	   (&playerTemp0,		"Assets/Ball3.obj", "tex_MinigolfPack.png",	basicShader);

	std::vector<char*> temp;
	temp.push_back("wood.png");
	temp.push_back("greenglass.jpg");
	colladaLoadFuncMulTex(&treeWithMultiTex,"tree.dae",		temp,						basicShader);

}

vector<GameObject*> TutorialGame::	AddSomeObject(MeshSceneNode* sceneNode, const Vector3& position, const Vector3& size, Quaternion rotate, std::string objectName)
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

		for each (Vector3 vert in newRender->GetMesh()->GetPositionData()) 
		{
			vert = tempScale * vert;
			verts.push_back(PxVec3(vert.x, vert.y, vert.z));
		}
		for each (unsigned int index in newRender->GetMesh()->GetIndexData())		tris.push_back(index);
		PxMaterial* mMaterial = PhysxController::getInstance().Physics()->createMaterial(0.99f, 0.99f, 0.5f);

		TriangleMeshPhysicsComponent* physicsC = new TriangleMeshPhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z), PxQuat(rotate.x, rotate.y, rotate.z, rotate.w)), tempObject, 10000, verts, tris, mMaterial);

		PhysxController::getInstance().setupFiltering(physicsC->getActor(), FilterGroup::eLEVEL, FilterGroup::ePLAYER);
		tempObject->addComponent(physicsC);

		resultList.push_back(tempObject);
		world->AddGameObject(tempObject);
	}
	return resultList;
}

GameObject* TutorialGame::			AddSphereObjectToWorld(MeshSceneNode* sceneNode, const Vector3& position, const Vector3& size, std::string objectName)
{
	GameObject* BallTemp = new GameObject();
	std::vector<RenderObject*> renderList = sceneNode->GetAllMesh();

	//BallTemp->setCamera(world->GetMainCamera());
	BallTemp->GetTransform().SetWorldScale(size);
	BallTemp->GetTransform().SetWorldPosition(position);

	OGLMesh* objOGL = new OGLMesh(renderList[0]->GetMesh());

	RenderObject* newRender = new RenderObject(renderList[0]);
	newRender->SetParentTransform(&BallTemp->GetTransform());
	BallTemp->SetRenderObject(newRender);

	OGLMesh* tempOGL = new OGLMesh(newRender->GetMesh());

	PxMaterial* mMaterial = PhysxController::getInstance().Physics()->createMaterial(0.99f, 0.99f, 1);
	SpherePhysicsComponent* sphere = new SpherePhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), BallTemp, 10, 0.05, mMaterial);
	PhysxController::getInstance().setupFiltering(sphere->getActor(), FilterGroup::ePLAYER, FilterGroup::eLEVEL);
	BallTemp->addComponent(sphere);

	sphere->setLinearDamping(0.8);
	sphere->setAngularDamping(2);


	world->AddGameObject(BallTemp);
	return BallTemp;
}

Player* TutorialGame::			AddPlayerObjectToWorld(MeshSceneNode* sceneNode, const Vector3& position, const Vector3& size, std::string objectName)
{
	//temp information
	int playerNum = 0;

	//real code
	Ball = new Player(playerNum);
	Ball->setCamera(world->GetMainCamera());

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


	//physics component
	SpherePhysicsComponent* sphere = nullptr;
	PxMaterial* mMaterial = PhysxController::getInstance().Physics()->createMaterial(0.99f, 0.99f, 1);
	sphere = new SpherePhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), Ball, 10, 0.05, mMaterial);
	Ball->addComponent(sphere);
	//Ball->addComponent(sphere);

	sphere->setLinearDamping(0.8);
	sphere->setAngularDamping(2);

	Ball->SetNetworkObject(new NetworkObject(*Ball, playerNum));

	Script* test = new Script();
	auto script = [](GameObject* (Ball)) {std::cout << "I am a Player" << std::endl; };
	test->setLambda(std::function<void(GameObject*)>(script));

	cubeDebuff* cubed = new cubeDebuff(objOGL, Ball->GetCubeMesh());
	Ball->addComponent(cubed);

	TestBuff* testBuff = new TestBuff();
	Ball->addComponent(testBuff);
	Ball->addComponent(new Homing(Vector3(0, 0, 3)));
	world->AddGameObject(Ball);

	return Ball;
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

	if (powerUpName.size() > 0)
		displayPowerUpText(dt);

	world->UpdateWorld(dt);
	renderer->Update(dt);
	SelectObject();
	Debug::FlushRenderables();
	renderer->Render();

	//update NetWork
	UpdateNetworkPostion(Ball);
	/*if (!isNetworkedGame) {
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NUM1)) {
		log->info("server");
		isNetworkedGame = true;
		isServer = true;
	}
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NUM2)) {
		log->info("client");
		isNetworkedGame = true;
	}

	return;
}*/


}

void TutorialGame::displayPowerUpText(float dt)
{
	renderer->DrawString(powerUpName, Vector2(500, 600));

	powerUpTxtTimer -= dt;

	if (powerUpTxtTimer <= 0) 
	{
		powerUpName.clear();
		powerUpTxtTimer = powerUpTxtLength;
	}
}

void TutorialGame::UpdateKeys() {
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::F1)) {
		InitWorld(); //We can reset the simulation at any time with F1
	}

	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::F2)) {
		UIworld->SetUIactive(false);
		//de something else
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
	renderer->DrawString("test wordssssssssss!", Vector2(10, 0));
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
		isServer = true;
		UIworld->SetUIactive(true); 
	};
	gameMode1->funL = intogame;

	auto servergame = [this]() { 
		isNetworkedGame = true;
		isServer = true;
		UIworld->SetUIactive(true);
	};
	gameMode2->funL = servergame;

	auto clientgame = [this]() { 
		isNetworkedGame = true;
		isServer = false;
		UIworld->SetUIactive(true);
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
	UIrenderer->DrawString("W S choose mode, D into select", Vector2(50, 0),Vector4(0,1,0,0));
	UIMachine->LoadUIState(UIrenderer);
	UpdateUIKeyWords(UIMachine);
	UIrenderer->Update(dt);
	UIrenderer->Render();
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



//followings codes are some useless code and check if can be deleted

/*


GameObject* TutorialGame::AddPlayerToWorld(Vector3 position, int playerNum)
{

	Ball = new Player(playerNum);

	Ball->setCamera(world->GetMainCamera());

	Ball->GetTransform().SetWorldScale(Vector3(1, 1, 1));

	Ball->SetCubeMesh(cubeMesh);
	Ball->SetPlayerMesh(playerMesh1);

	SpherePhysicsComponent* sphere = nullptr;

	PxMaterial* mMaterial = PhysxController::getInstance().Physics()->createMaterial(0.99f, 0.99f, 1);

	OGLMesh* thisMesh = playerMesh1;
	Ball->SetRenderObject(
		new RenderObject(&Ball->GetTransform(), playerMesh1, golfLevelTex, basicShader));
	sphere = new SpherePhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), Ball, 10, 0.05, mMaterial);
	thisMesh = playerMesh1;

	Ball->addComponent(sphere);


	sphere->setLinearDamping(0.8);
	sphere->setAngularDamping(2);

	Ball->SetNetworkObject(new NetworkObject(*Ball, playerNum));

	Script* test = new Script();
	auto script = [](GameObject* (Ball)) {std::cout << "I am a Player" << std::endl; };
	test->setLambda(std::function<void(GameObject*)>(script));

	cubeDebuff* cubed = new cubeDebuff(thisMesh, Ball->GetCubeMesh());
	Ball->addComponent(cubed);

	TestBuff* testBuff = new TestBuff();
	Ball->addComponent(testBuff);
	Ball->addComponent(new Homing(Vector3(0, 0, 3)));
	world->AddGameObject(Ball);

	return Ball;
}


void TutorialGame::DebugObjectMovement() {
//If we've selected an object, we can manipulate it with some key presses
	if (inSelectionMode && selectionObject) {
		//Twist the selected object!
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::LEFT)) {
			selectionObject->GetPhysicsObject()->AddTorque(Vector3(-10, 0, 0));
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::RIGHT)) {
			selectionObject->GetPhysicsObject()->AddTorque(Vector3(10, 0, 0));
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::NUM7)) {
			selectionObject->GetPhysicsObject()->AddTorque(Vector3(0, 10, 0));
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::NUM8)) {
			selectionObject->GetPhysicsObject()->AddTorque(Vector3(0, -10, 0));
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::RIGHT)) {
			selectionObject->GetPhysicsObject()->AddTorque(Vector3(10, 0, 0));
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::UP)) {
			selectionObject->GetPhysicsObject()->AddForce(Vector3(0, 0, -10));
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::DOWN)) {
			selectionObject->GetPhysicsObject()->AddForce(Vector3(0, 0, 10));
		}

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::NUM5)) {
			selectionObject->GetPhysicsObject()->AddForce(Vector3(0, -10, 0));
		}
	}
}
void  TutorialGame::LockedCameraMovement() {
	if (lockedObject != nullptr) {
		Vector3 objPos = lockedObject->GetTransform().GetWorldPosition();
		Vector3 camPos = objPos + lockedOffset;

		Matrix4 temp = Matrix4::BuildViewMatrix(camPos, objPos, Vector3(0, 1, 0));

		Matrix4 modelMat = temp.Inverse();

		Quaternion q(modelMat);
		Vector3 angles = q.ToEuler(); //nearly there now!

		world->GetMainCamera()->SetPosition(camPos);
		world->GetMainCamera()->SetPitch(angles.x);
		world->GetMainCamera()->SetYaw(angles.y);
	}
}

void TutorialGame::LockedObjectMovement() {
	Matrix4 view		= world->GetMainCamera()->BuildViewMatrix();
	Matrix4 camWorld	= view.Inverse();

	Vector3 rightAxis = Vector3(camWorld.GetColumn(0)); //view is inverse of model!

	//forward is more tricky -  camera forward is 'into' the screen...
	//so we can take a guess, and use the cross of straight up, and
	//the right axis, to hopefully get a vector that's good enough!

	Vector3 fwdAxis = Vector3::Cross(Vector3(0, 1, 0), rightAxis);

	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::LEFT)) {
		selectionObject->GetPhysicsObject()->AddForce(-rightAxis);
	}

	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::RIGHT)) {
		selectionObject->GetPhysicsObject()->AddForce(rightAxis);
	}

	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::UP)) {
		selectionObject->GetPhysicsObject()->AddForce(fwdAxis);
	}

	if (Window::GetKeyboard()->KeyDown(KeyboardKeys::DOWN)) {
		selectionObject->GetPhysicsObject()->AddForce(-fwdAxis);
	}
}

void TutorialGame::MoveSelectedObject() {
	renderer -> DrawString(" Click Force :" + std::to_string(forceMagnitude),
		Vector2(10, 20)); // Draw debug text at 10 ,20
	forceMagnitude += Window::GetMouse() -> GetWheelMovement() * 100.0f;

	if (!selectionObject) {
		return;// we haven �t selected anything !

	}
	// Push the selected object !
	if (Window::GetMouse() -> ButtonPressed(NCL::MouseButtons::RIGHT)) {
		Ray ray = CollisionDetection::BuildRayFromMouse(
			* world -> GetMainCamera());

		RayCollision closestCollision;
		if (world -> Raycast(ray, closestCollision, true)) {
			if (closestCollision.node == selectionObject) {
				selectionObject -> GetPhysicsObject() -> AddForceAtPosition(
					ray.GetDirection() * forceMagnitude,
					closestCollision.collidedAt);

			}

		}

	}
}


void TutorialGame::SeenObjects() {


	GameObjectIterator first;
	GameObjectIterator last;
	world->GetObjectIterators(first, last);

	for (vector<GameObject*>::const_iterator i = first;
			i != last; i++) {

		Ray ray = CollisionDetection::BuildRayToCamera(*world->GetMainCamera(), **i);

		GameObject* obj = *i;

		RayCollision closestCollision;
		if (!world->Raycast(ray, closestCollision, true)) {

			obj->GetRenderObject()->SetColour(Vector4(1, 0, 0, 1));
		}
		else
		{
			obj->GetRenderObject()->SetColour(Vector4(0, 0, 0, 1));
		}
	}
}

void TutorialGame::RenderScoreBoard()
{
	float size = 1.0f;
	float inverseMass = 0.1f;

	Player* otherBall = new Player(playerNum);
	if (isServer)
	{
		renderer->DrawString("YOUR TOTAL SCORE: " + std::to_string(world->GetPlayerOneTotal()),
			Vector2(400, 400), Vector4(0, 0, 1, 1));
		renderer->DrawString("THEIR TOTAL SCORE: " + std::to_string(world->GetPlayerTwoTotal()),
			Vector2(400, 350), Vector4(1, 0, 0, 1));
	}
	else
	{
		renderer->DrawString("YOUR TOTAL SCORE: " + std::to_string(world->GetPlayerTwoTotal()),
			Vector2(400, 400), Vector4(1, 0, 0, 1));
		renderer->DrawString("THEIR TOTAL SCORE: " + std::to_string(world->GetPlayerOneTotal()),
			Vector2(400, 350), Vector4(0, 0, 1, 1));
	}
}


void TutorialGame::ResetCamera() {
	world->GetMainCamera()->SetNearPlane(0.0f);
	world->GetMainCamera()->SetFarPlane(0.0f);
	world->GetMainCamera()->SetPitch(0.0f);
	world->GetMainCamera()->SetYaw(0.0f);
	world->GetMainCamera()->SetPosition(Vector3(0, 0, 0));
	lockedObject = nullptr;
}


void TutorialGame::RestartNetworkedGame()
{
	//StoreHighScore();
	newSession = false;
	playing = true;
	world->setPlayerOneScore(0);
	world->setPlayerTwoScore(0);
	Vector3 offSet(275, 10, 195);
	matchTimer = 100;
	Ball->GetNetworkObject()->resetScore();
	playerTwo->GetNetworkObject()->resetScore();
	physics->Clear();

	if (isServer)
	{
		Ball->GetTransform().SetWorldPosition(offSet + Vector3(5, 0, 5));
		playerTwo->GetTransform().SetWorldPosition(offSet - Vector3(5, 0, 5));
	}

	std::vector <GameObject*>::const_iterator first;
	std::vector <GameObject*>::const_iterator last;

	world->GetObjectIterators(first, last);

	int collectableCounter = 0;

	otherBall->SetNetworkObject(new NetworkObject(*otherBall, playerNum));

	world->AddGameObject(otherBall);
	serverPlayers.insert(std::pair<int, GameObject*>(playerNum, otherBall));
	for (auto i = first; i != last; ++i)
	{
		// Reset Collectables
		if ((*i)->getLayer() == 4)
		{
			(*i)->setLayerMask(4);
			int xPos = rand() % 480;
			int zPos = rand() % 420;
			(*i)->GetTransform().SetWorldPosition(Vector3(xPos, 10, zPos));
			(*i)->GetRenderObject()->SetColour(Vector4(1, 1, 0, 1));
			collectableCounter++;
		}

		// Reset Enemies
		if ((*i)->getLayer() == 3)
		{
			Enemy* e = (Enemy*)(*i);
			e->resetPosition();
		}
	}

	world->SetCollectableCount(collectableCounter);
}


GameObject* TutorialGame::AddGolfLevelToWorld(const Vector3& position, const Vector3& size, const Vector4& colour, int index) {
	GameObject* floor = new GameObject("FLOOR");
	floor->setLayer(1);
	floor->setLayerMask(49);
	//floor->SetBoundingVolume((CollisionVolume*)volume);
	floor->GetTransform().SetWorldScale(Vector3(1, 1, 1));
	floor->GetTransform().SetWorldPosition(position + Vector3(150, 150, 150));
	std::vector<PxVec3> verts;
	std::vector<PxU32> tris;
	for each (Vector3 vert in golfLevelMeshes[index]->GetPositionData()) {
		verts.push_back(PxVec3(vert.x, vert.y, vert.z));
	}
	for each (unsigned int index in golfLevelMeshes[index]->GetIndexData()) {
		tris.push_back(index);
	}
	TriangleMeshPhysicsComponent* physicsC = nullptr;
	PxMaterial* mMaterial = PhysxController::getInstance().Physics()->createMaterial(0.99f, 0.99f, 0.5f);
	physicsC = new TriangleMeshPhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), floor, 10000, verts, tris, mMaterial);
	PhysxController::getInstance().setupFiltering(physicsC->getActor(), FilterGroup::eLEVEL, FilterGroup::ePLAYER);
	floor->addComponent(physicsC);
	floor->SetRenderObject(new RenderObject(&floor->GetTransform(), golfLevelMeshes[index], golfLevelTex, basicShader));
	//floor->SetPhysicsObject(new PhysicsObject(&floor->GetTransform(), floor->GetBoundingVolume()));
	//floor->GetPhysicsObject()->SetInverseMass(0);
	//floor->GetPhysicsObject()->InitCubeInertia();
	world->AddGameObject(floor);
	return floor;
}


GameObject* TutorialGame::AddOtherPlayerToWorld(Vector3 position, int playerNum)
{
	float size = 1.0f;
	float inverseMass = 0.1f;

	GameObject* otherBall = new GameObject();

	//SphereVolume* volume = new SphereVolume(size);
	//otherBall->SetBoundingVolume((CollisionVolume*)volume);

	BoxPhysicsComponent* box = new BoxPhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)), Ball,10,0.05, 0.05, 0.05);
	PhysxController::getInstance().setupFiltering(box->getActor(), FilterGroup::ePLAYER, FilterGroup::eLEVEL);
	Ball->addComponent(box);

otherBall->GetTransform().SetWorldScale(Vector3(size, size, size));

SpherePhysicsComponent* sphere = nullptr;

PxMaterial* mMaterial = PhysxController::getInstance().Physics()->createMaterial(2, 0.5, 1);

switch (playerNum)
{
case 1: otherBall->SetRenderObject(new RenderObject(&otherBall->GetTransform(), playerMesh1, golfLevelTex, basicShader));
	sphere = new SpherePhysicsComponent(PxTransform(PxVec3(playerPos1.x, playerPos1.y, playerPos1.z)), 10, 0.05, mMaterial);
	break;
case 2: otherBall->SetRenderObject(new RenderObject(&otherBall->GetTransform(), playerMesh2, golfLevelTex, basicShader));
	sphere = new SpherePhysicsComponent(PxTransform(PxVec3(playerPos2.x, playerPos2.y, playerPos2.z)), 10, 0.05, mMaterial);
	break;
case 3: otherBall->SetRenderObject(new RenderObject(&otherBall->GetTransform(), playerMesh3, golfLevelTex, basicShader));
	sphere = new SpherePhysicsComponent(PxTransform(PxVec3(playerPos3.x, playerPos3.y, playerPos3.z)), 10, 0.05, mMaterial);
	break;
case 4: otherBall->SetRenderObject(new RenderObject(&otherBall->GetTransform(), playerMesh4, golfLevelTex, basicShader));
	sphere = new SpherePhysicsComponent(PxTransform(PxVec3(playerPos4.x, playerPos4.y, playerPos4.z)), 10, 0.05, mMaterial);
	break;
}

otherBall->addComponent(sphere);

sphere->setLinearDamping(0.8);
sphere->setAngularDamping(2);

otherBall->SetPhysicsObject(new PhysicsObject(&otherBall->GetTransform(), otherBall->GetBoundingVolume()));

otherBall->GetPhysicsObject()->SetInverseMass(inverseMass);
otherBall->GetPhysicsObject()->InitSphereInertia();

otherBall->SetNetworkObject(new NetworkObject(*otherBall, playerID));

world->AddGameObject(otherBall);

return otherBall;
}


void TutorialGame::StoreHighScore()
{
	std::ofstream myfile;
	myfile.open(fileName, std::ifstream::out, std::ifstream::trunc);

	myfile << "HIGH SCORES FROM LAST MATCH" << "\n";

	myfile << "Player One (Blue): " << std::to_string(world->GetPlayerOneTotal()) << "\n";

	myfile << "Player Two (Red): " << std::to_string(world->GetPlayerTwoTotal()) << "\n";

	myfile.close();
}

void TutorialGame::RenderMenu()
{
	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::DOWN) && buttonSelected != 4) {

		buttonSelected++;
	}

	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::UP) && buttonSelected != 1) {

		buttonSelected--;
	}

	if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::RETURN)) {
	TriangleMeshPhysicsComponent* physicsC = new TriangleMeshPhysicsComponent(PxTransform(PxVec3(position.x, position.y, position.z)),floor, 10000, verts, tris);
	floor->addComponent(physicsC);
	PhysxController::getInstance().setupFiltering(physicsC->getActor(), FilterGroup::eLEVEL, FilterGroup::ePLAYER);

		switch (buttonSelected)
		{
		case 1: playing = true;
				playerID = 1000;
				isServer = true;
				StartGame();
				return;
		case 2: playerID = 2000;
				playing = true;
				isNetworkedGame = true;
				world->SetIsNetworkedGame(true);
				StartGame();
				return;
		case 3: playerID = 1000;
				playing = true;
				isNetworkedGame = true;
				world->SetIsServer(true);
				world->SetIsNetworkedGame(true);
				isServer = true;
				StartGame();
				return;
		case 4: exit(0);
		}
	}

	switch (buttonSelected)
	{
	case 1 : renderer->DrawString("Play Singleplayer",
					Vector2(40, 600), Vector4(0, 0, 1, 1));
			renderer->DrawString("Play Multiplayer",
						Vector2(40, 500));
			renderer->DrawString("Play Multiplayer as Server",
				Vector2(40, 400));
			renderer->DrawString("Exit",
				Vector2(40, 300));

	case 2 : renderer->DrawString("Play Singleplayer",
				Vector2(40, 600));
			renderer->DrawString("Play Multiplayer",
				Vector2(40, 500), Vector4(0, 0, 1, 1));
			renderer->DrawString("Play Multiplayer as Server",
				Vector2(40, 400));
			renderer->DrawString("Exit",
				Vector2(40, 300));

	case 3 : renderer->DrawString("Play Singleplayer",
				Vector2(40, 600));
			renderer->DrawString("Play Multiplayer",
				Vector2(40, 500));
			renderer->DrawString("Play Multiplayer as Server",
				Vector2(40, 400), Vector4(0, 0, 1, 1));
			renderer->DrawString("Exit",
				Vector2(40, 300));
	case 4: renderer->DrawString("Play Singleplayer",
			Vector2(40, 600));
			renderer->DrawString("Play Multiplayer",
				Vector2(40, 500));
			renderer->DrawString("Play Multiplayer as Server",
				Vector2(40, 400));
			renderer->DrawString("Exit",
				Vector2(40, 300), Vector4(0, 0, 1, 1));

	}
}


//From here on it's functions to add in objects to the world!
void TutorialGame::AddObstacles()
{
	Vector4 brown = Vector4(0.58, 0.29, 0, 1);

	AddTerrainToWorld(Vector3(430, 18, 150), Vector3(55, 10, 5), brown);
	AddTerrainToWorld(Vector3(380, 18, 165), Vector3(5, 10, 10), brown);
	AddTerrainToWorld(Vector3(360, 18, 170), Vector3(15, 10, 5), brown);
	AddTerrainToWorld(Vector3(430, 18, 180), Vector3(5, 10, 15), brown);
	AddTerrainToWorld(Vector3(405, 18, 190), Vector3(30, 10, 5), brown);
	AddTerrainToWorld(Vector3(380, 18, 210), Vector3(5, 10, 15), brown);
	AddTerrainToWorld(Vector3(365, 18, 230), Vector3(45, 10, 5), brown);
	AddTerrainToWorld(Vector3(455, 18, 230), Vector3(20, 10, 5), brown);

	Vector3 offset(-310, 0, 10);

	AddTerrainToWorld(Vector3(20, 18, 140), Vector3(30, 10, 5), brown);
	AddTerrainToWorld(offset + Vector3(430, 18, 150), Vector3(55, 10, 5), brown);
	AddTerrainToWorld(offset + Vector3(380, 18, 165), Vector3(5, 10, 10), brown);
	AddTerrainToWorld(offset + Vector3(360, 18, 170), Vector3(15, 10, 5), brown);
	AddTerrainToWorld(offset + Vector3(430, 18, 180), Vector3(5, 10, 15), brown);
	AddTerrainToWorld(offset + Vector3(405, 18, 190), Vector3(30, 10, 5), brown);
	AddTerrainToWorld(offset + Vector3(380, 18, 210), Vector3(5, 10, 15), brown);
	AddTerrainToWorld(offset + Vector3(365, 18, 230), Vector3(45, 10, 5), brown);
	AddTerrainToWorld(offset + Vector3(455, 18, 230), Vector3(20, 10, 5), brown);
}

//A single function to add a large immoveable cube to the bottom of our world
GameObject* TutorialGame::AddFloorToWorld(const Vector3& position) {
	GameObject* floor = new GameObject("FLOOR");

	Vector3 floorSize = Vector3(300, 2, 300);
	AABBVolume* volume = new AABBVolume(floorSize);
	floor->SetBoundingVolume((CollisionVolume*)volume);
	floor->GetTransform().SetWorldScale(floorSize);
	floor->GetTransform().SetWorldPosition(position);

	floor->SetRenderObject(new RenderObject(&floor->GetTransform(), cubeMesh, nullptr, basicShader));
	floor->SetPhysicsObject(new PhysicsObject(&floor->GetTransform(), floor->GetBoundingVolume()));

	floor->GetRenderObject()->SetColour(Vector4(0, 0.6, 0, 1));

	floor->GetPhysicsObject()->SetInverseMass(0);
	floor->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(floor);

	return floor;
}

GameObject* TutorialGame::AddTerrainToWorld(const Vector3& position, const Vector3& size, const Vector4& colour) {
	GameObject* floor = new GameObject("FLOOR");

	floor->setLayer(1);
	floor->setLayerMask(49);

	AABBVolume* volume = new AABBVolume(size);
	floor->SetBoundingVolume((CollisionVolume*)volume);
	floor->GetTransform().SetWorldScale(size);
	floor->GetTransform().SetWorldPosition(position);

	floor->SetRenderObject(new RenderObject(&floor->GetTransform(), cubeMesh, basicTex, basicShader));
	floor->SetPhysicsObject(new PhysicsObject(&floor->GetTransform(), floor->GetBoundingVolume()));

	floor->GetRenderObject()->SetColour(colour);

	floor->GetPhysicsObject()->SetInverseMass(0);
	floor->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(floor);

	return floor;
}

GameObject* TutorialGame::AddLakeToWorld(const Vector3& position, const Vector3& size, const Vector4& colour) {
	GameObject* floor = new GameObject("LAKE");

	floor->setLayer(6);
	floor->setLayerMask(49);

	Vector3 colliderSize = size;
	colliderSize.y -= 1.2;
	AABBVolume* volume = new AABBVolume(colliderSize);
	floor->SetBoundingVolume((CollisionVolume*)volume);
	floor->GetTransform().SetWorldScale(size);
	floor->GetTransform().SetWorldPosition(position);

	floor->SetRenderObject(new RenderObject(&floor->GetTransform(), cubeMesh, basicTex, basicShader));
	floor->SetPhysicsObject(new PhysicsObject(&floor->GetTransform(), floor->GetBoundingVolume()));

	floor->GetRenderObject()->SetColour(colour);

	floor->GetPhysicsObject()->SetInverseMass(0);
	floor->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(floor);

	return floor;
}

void TutorialGame::AddBridgeToWorld(Vector3 startPos, int num) {
	Vector3 cubeSize = Vector3(1, 1, 10);

	float	invCubeMass = 0.01;
	int		numLinks = 55;
	float	maxDistance = 1.2;
	float	cubeDistance = 2;

	int layerMask = 53;

	Vector4 brown = Vector4(0.58, 0.29, 0, 1);

	//Vector3 startPos = Vector3(36, 7, 15);

	Vector3 endPos = startPos;

	if (num == 1)
	{
		endPos.y += 19;
	}
	else if (num == 2)
	{
		startPos.y += 19;
		numLinks = 47;
	}
	else 
	{
		startPos.y += 19;
		endPos.y += 19;
		numLinks = 100;
	}

	GameObject* start = AddCubeToWorld(startPos + Vector3(0, 0, 0), cubeSize, 0);

	start->setLayer(1);
	start->setLayerMask(layerMask);

	start->GetRenderObject()->SetColour(brown);
	

	GameObject* end = AddCubeToWorld(endPos + Vector3((numLinks + 2) * cubeDistance, 0, 0), cubeSize, 0);

	end->setLayer(1);
	end->setLayerMask(layerMask);

	end->GetRenderObject()->SetColour(brown);

	GameObject* previous = start;

	for (int i = 0; i < numLinks; ++i) {
		GameObject* block = AddCubeToWorld(startPos + Vector3((i + 1) * cubeDistance, 0, 0), cubeSize, invCubeMass);
		
		block->setLayer(1);
		block->setLayerMask(layerMask);
		
		block->GetRenderObject()->SetColour(brown);
		PositionConstraint* constraint = new PositionConstraint(previous, block, maxDistance);
		world->AddConstraint(constraint);
		previous = block;
	}

	PositionConstraint* constraint = new PositionConstraint(previous, end, maxDistance);
	world->AddConstraint(constraint);
}


//Builds a game object that uses a sphere mesh for its graphics, and a bounding sphere for its
//rigid body representation. This and the cube function will let you build a lot of 'simple' 
//physics worlds. You'll probably need another function for the creation of OBB cubes too.
GameObject* TutorialGame::AddSphereToWorld(const Vector3& position, float radius, float inverseMass) {
	GameObject* sphere = new GameObject("SPHERE");

	Vector3 sphereSize = Vector3(radius, radius, radius);
	SphereVolume* volume = new SphereVolume(radius);
	sphere->SetBoundingVolume((CollisionVolume*)volume);
	sphere->GetTransform().SetWorldScale(sphereSize);
	sphere->GetTransform().SetWorldPosition(position);

	sphere->SetRenderObject(new RenderObject(&sphere->GetTransform(), sphereMesh, basicTex, basicShader));
	sphere->SetPhysicsObject(new PhysicsObject(&sphere->GetTransform(), sphere->GetBoundingVolume()));

	sphere->GetPhysicsObject()->SetInverseMass(inverseMass);
	sphere->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(sphere);

	return sphere;
}

GameObject* TutorialGame::AddCubeToWorld(const Vector3& position, Vector3 dimensions, float inverseMass) {
	GameObject* cube = new GameObject("CUBE");

	AABBVolume* volume = new AABBVolume(dimensions);

	//SphereVolume* volume = new SphereVolume(dimensions.x);

	cube->SetBoundingVolume((CollisionVolume*)volume);

	cube->GetTransform().SetWorldPosition(position);
	cube->GetTransform().SetWorldScale(dimensions);

	cube->SetRenderObject(new RenderObject(&cube->GetTransform(), cubeMesh, basicTex, basicShader));
	cube->SetPhysicsObject(new PhysicsObject(&cube->GetTransform(), cube->GetBoundingVolume()));

	cube->GetPhysicsObject()->SetInverseMass(inverseMass);
	cube->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(cube);

	return cube;
}

GameObject* TutorialGame::AddPlayerTwoToWorld(const Vector3& position)
{
	float inverseMass = 0.1f;

	playerTwo->SetRenderObject(new RenderObject(&playerTwo->GetTransform(), gooseMesh, nullptr, basicShader));
	playerTwo->SetPhysicsObject(new PhysicsObject(&playerTwo->GetTransform(), playerTwo->GetBoundingVolume()));

	playerTwo->GetPhysicsObject()->SetInverseMass(inverseMass);
	playerTwo->GetPhysicsObject()->InitSphereInertia();

	int id;
	if (playerID == 1000)
	{
		id = 2000;
		playerTwo->GetRenderObject()->SetColour(Vector4(1, 0, 0, 1));
	}
	else 
	{
		id = 1000;
		playerTwo->GetRenderObject()->SetColour(Vector4(0, 0, 1, 1));
	}
		
	playerTwo->SetNetworkObject(new NetworkObject(*playerTwo, id));

	world->AddGameObject(playerTwo);

	return playerTwo;
}

Enemy* TutorialGame::AddParkKeeperToWorld(const Vector3& position)
{
	float meshSize = 4.0f;
	float inverseMass = 0.5f;

	Enemy* keeper = new Enemy(position, world, isServer);

	keeper->setPlayer(Ball);
	keeper->setPlayerTwo(playerTwo);
	AABBVolume* volume = new AABBVolume(Vector3(0.3, 0.9f, 0.3) * meshSize);
	keeper->SetBoundingVolume((CollisionVolume*)volume);

	keeper->GetTransform().SetWorldScale(Vector3(meshSize, meshSize, meshSize));

	keeper->SetRenderObject(new RenderObject(&keeper->GetTransform(), keeperMesh, nullptr, basicShader));
	keeper->SetPhysicsObject(new PhysicsObject(&keeper->GetTransform(), keeper->GetBoundingVolume()));

	keeper->GetPhysicsObject()->SetInverseMass(inverseMass);
	keeper->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(keeper);

	return keeper;
	
}

GameObject* TutorialGame::AddCharacterToWorld(const Vector3& position) {
	float meshSize = 4.0f;
	float inverseMass = 0.5f;

	auto pos = keeperMesh->GetPositionData();

	Vector3 minVal = pos[0];
	Vector3 maxVal = pos[0];

	for (auto& i : pos) {
		maxVal.y = max(maxVal.y, i.y);
		minVal.y = min(minVal.y, i.y);
	}

	GameObject* character = new GameObject("CHARACTER");

	float r = rand() / (float)RAND_MAX;


	AABBVolume* volume = new AABBVolume(Vector3(0.3, 0.9f, 0.3) * meshSize);
	character->SetBoundingVolume((CollisionVolume*)volume);

	character->GetTransform().SetWorldScale(Vector3(meshSize, meshSize, meshSize));
	character->GetTransform().SetWorldPosition(position);

	character->SetRenderObject(new RenderObject(&character->GetTransform(), r > 0.5f ? charA : charB, nullptr, basicShader));
	character->SetPhysicsObject(new PhysicsObject(&character->GetTransform(), character->GetBoundingVolume()));

	character->GetPhysicsObject()->SetInverseMass(inverseMass);
	character->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(character);

	return character;
}

GameObject* TutorialGame::AddAppleToWorld(const Vector3& position) {
	Collectable* apple = new Collectable(10, position);

	SphereVolume* volume = new SphereVolume(0.7f);
	apple->SetBoundingVolume((CollisionVolume*)volume);
	apple->GetTransform().SetWorldScale(Vector3(4, 4, 4));
	apple->GetTransform().SetWorldPosition(position);

	apple->SetRenderObject(new RenderObject(&apple->GetTransform(), appleMesh, nullptr, basicShader));
	apple->SetPhysicsObject(new PhysicsObject(&apple->GetTransform(), apple->GetBoundingVolume()));

	apple->GetPhysicsObject()->SetInverseMass(100.0f);
	apple->GetPhysicsObject()->InitSphereInertia();
	apple->GetRenderObject()->SetColour(Vector4(1, 1, 0, 1));

	world->AddGameObject(apple);

	return apple;
}

GameObject* TutorialGame::AddBonusItemToWorld(const Vector3& position) {
	Collectable* box = new Collectable(20, position);

	AABBVolume* volume = new AABBVolume(Vector3(0.8, 0.8, 0.8));
	box->SetBoundingVolume((CollisionVolume*)volume);
	box->GetTransform().SetWorldScale(Vector3(0.8, 0.8, 0.8));
	box->GetTransform().SetWorldPosition(position);

	box->SetRenderObject(new RenderObject(&box->GetTransform(), cubeMesh, nullptr, basicShader));
	box->SetPhysicsObject(new PhysicsObject(&box->GetTransform(), box->GetBoundingVolume()));
	box->GetRenderObject()->SetColour(Vector4(1, 1, 0, 1));

	box->GetPhysicsObject()->SetInverseMass(100.0f);
	box->GetPhysicsObject()->InitSphereInertia();

	world->AddGameObject(box);

	return box;
}

void TutorialGame::InitSphereGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, float radius) {
	for (int x = 0; x < numCols; ++x) {
		for (int z = 0; z < numRows; ++z) {
			Vector3 position = Vector3(x * colSpacing, 10.0f, z * rowSpacing);
			AddSphereToWorld(position, radius, 1.0f);
		}
	}
	//AddFloorToWorld(Vector3(0, -2, 0));
}

void TutorialGame::InitMixedGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing) {
	float sphereRadius = 1.0f;
	Vector3 cubeDims = Vector3(1, 1, 1);

	for (int x = 0; x < numCols; ++x) {
		for (int z = 0; z < numRows; ++z) {
			Vector3 position = Vector3(x * colSpacing, 10.0f, z * rowSpacing);

			if (rand() % 2) {
				AddCubeToWorld(position, cubeDims);
			}
			else {
				AddSphereToWorld(position, sphereRadius);
			}
		}
	}
	//AddFloorToWorld(Vector3(0, -2, 0));
}

void TutorialGame::InitCubeGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, const Vector3& cubeDims) {
	for (int x = 1; x < numCols+1; ++x) {
		for (int z = 1; z < numRows+1; ++z) {
			Vector3 position = Vector3(x * colSpacing, 10.0f, z * rowSpacing);
			AddCubeToWorld(position, cubeDims, 1.0f);
		}
	}
	//AddFloorToWorld(Vector3(0, -2, 0));
}

void TutorialGame::SimpleGJKTest() {
	Vector3 dimensions		= Vector3(5, 5, 5);
	Vector3 floorDimensions = Vector3(100, 2, 100);

	GameObject* fallingCube = AddCubeToWorld(Vector3(0, 20, 0), dimensions, 10.0f);
	GameObject* newFloor	= AddCubeToWorld(Vector3(0, 0, 0), floorDimensions, 0.0f);

	delete fallingCube->GetBoundingVolume();
	delete newFloor->GetBoundingVolume();

	fallingCube->SetBoundingVolume((CollisionVolume*)new OBBVolume(dimensions));
	newFloor->SetBoundingVolume((CollisionVolume*)new OBBVolume(floorDimensions));

}
*/
