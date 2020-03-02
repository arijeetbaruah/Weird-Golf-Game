#include "ExampleRenderer.h"
#include "RenderObject.h"
#include "../Plugins/PlayStation4/PS4Window.h"
#include "../Plugins/PlayStation4/PS4Shader.h"
#include "../Plugins/PlayStation4/PS4Mesh.h"

using namespace NCL;
using namespace NCL::PS4;

ExampleRenderer::ExampleRenderer(PS4Window* window, PS4Input* input) : 
	PS4RendererBase(window), input(input)
{
	defaultShader = PS4Shader::GenerateShader(
		"/app0/Assets/Shaders/PS4/VertexShader.sb",
		"/app0/Assets/Shaders/PS4/PixelShader.sb"
	);

	computeTest = new PS4ComputeShader("/app0/Assets/Shaders/PS4/ComputeShader.sb");

	defaultMesh = PS4Mesh::GenerateTriangle();
	defaultTexture = PS4Texture::LoadTextureFromFile("/app0/Assets/Textures/doge.gnf");

	testlevelTexture = PS4Texture::LoadTextureFromFile("/app0/Assets/Textures/tex_MinigolfPack.gnf");

	viewProjMat = (Matrix4*)onionAllocator.allocate(sizeof(Matrix4), Gnm::kEmbeddedDataAlignment4);
	*viewProjMat = Matrix4();

	cameraBuffer.initAsConstantBuffer(viewProjMat, sizeof(Matrix4));
	cameraBuffer.setResourceMemoryType(Gnm::kResourceMemoryTypeRO); // it's a constant buffer, so read-only is OK

	computeResult = (float*)onionAllocator.allocate(4, Gnm::kEmbeddedDataAlignment4);

	mainCamera = Camera(0, 0, Vector3(0, 0, 0));
	scePadSetMotionSensorState(input->GetPadHandle(), true);
	scePadResetOrientation(input->GetPadHandle());

	building = new SceneNode("/app0/Assets/Meshes/building.dae", defaultShader, PS4Texture::LoadTextureFromFile("/app0/Assets/Textures/monu10.gnf"));
	golfLevel = new SceneNode("/app0/Assets/Meshes/TestLevel2.dae", defaultShader, testlevelTexture);
	
	golfLevel->SetScale(Matrix4::Scale(Vector3(20, 20, 20)));
	golfLevel->Translate(Vector3(0, -10, 0));
	building->SetScale(Matrix4::Scale(Vector3(1, 1, 1)));
	building->Translate(Vector3(0, -10, -5));
	golfLevel->AddChild(building);
}

ExampleRenderer::~ExampleRenderer()	
{
	delete defaultMesh;
	delete defaultTexture;
	delete defaultShader;
	delete computeTest;
	delete testlevelTexture;
	delete golfLevel;
	delete building;
}

void ExampleRenderer::Update(float dt)	{
	time = dt;
	golfLevel->Update();
	input->Poll();

	if (input->GetButton(0)) 
	{
		std::cout << "LOL BUTTON" << std::endl;
		golfLevel->Translate(Vector3(0, 0, 0.1f));
	}
	auto axisL = input->GetAxis(0);
	auto currentPos = mainCamera.GetPosition();
	if (abs(axisL.y) < 0.1f)
	{
		axisL.y = 0;
	}
	if (abs(axisL.x) < 0.1f)
	{
		axisL.x = 0;
	}
	currentPos += mainCamera.BuildViewMatrix().GetTransposedRotation() *
		NCL::Vector3(0, 0, 1) * axisL.y * 0.2f;
	currentPos += mainCamera.BuildViewMatrix().GetTransposedRotation() * NCL::Vector3(1, 0, 0) * axisL.x * 0.2f;
	mainCamera.SetPosition(currentPos);

	auto axisR = input->GetAxis(1);
	if (abs(axisR.y) < 0.1f)
	{
		axisR.y = 0;
	}
	if (abs(axisR.x) < 0.1f)
	{
		axisR.x = 0;
	}
	auto pitch = mainCamera.GetPitch();
	auto yaw = mainCamera.GetYaw();
	pitch -= axisR.y;
	yaw -= axisR.x;
	mainCamera.SetPitch(pitch);
	mainCamera.SetYaw(yaw);
}

void ExampleRenderer::UpdateRotationAmount(float dt) {
	float* tempTime = (float*)currentGFXContext->allocateFromCommandBuffer(sizeof(float), Gnm::kEmbeddedDataAlignment4);
	*tempTime = dt;

	Gnm::Buffer inputBuffer;
	inputBuffer.initAsConstantBuffer(tempTime, sizeof(float)); //since newValue is in the command buffer, it'll persist past this function
	inputBuffer.setResourceMemoryType(Gnm::kResourceMemoryTypeRO); // it's a constant buffer, so read-only is OK

	Gnm::Buffer outputBuffer;
	outputBuffer.initAsRegularBuffer(computeResult, sizeof(float), 1); //since newValue is in the command buffer, it'll persist past this function
	outputBuffer.setResourceMemoryType(Gnm::kResourceMemoryTypeSC); // Make this buffer coherent

	int rotationIndex	= computeTest->GetRegularBuffer("rotationAmount");
	int timeIndex		= computeTest->GetConstantBuffer("InputData");

	currentGFXContext->setRwBuffers(Gnm::kShaderStageCs, rotationIndex, 1, &outputBuffer);
	currentGFXContext->setConstantBuffers(Gnm::kShaderStageCs, timeIndex, 1, &inputBuffer);

	computeTest->Bind(*currentGFXContext);
	computeTest->Execute(*currentGFXContext, 1,1,1);
	computeTest->Synchronize(*currentGFXContext);	//at this point, our rotation value will have been calculated by the compute shader...
}

void ExampleRenderer::RenderActiveScene() 
{
	std::queue<SceneNode*> q;
	q.push(golfLevel);
	while (!q.empty())
	{
		auto* item = q.front();
		q.pop();
		for (auto* child : item->GetChildren())
		{
			q.push(child);
		}
		for (const auto& object : item->GetRenderObjects())
		{
			DrawRenderObject(object.get());
		}
	}
}

void ExampleRenderer::DrawRenderObject(RenderObject* o) {
	Matrix4* transformMat = (Matrix4*)currentGFXContext->allocateFromCommandBuffer(sizeof(Matrix4), Gnm::kEmbeddedDataAlignment4);
	*transformMat = o->GetLocalTransform();

	Gnm::Buffer constantBuffer;
	constantBuffer.initAsConstantBuffer(transformMat, sizeof(Matrix4));
	constantBuffer.setResourceMemoryType(Gnm::kResourceMemoryTypeRO); // it's a constant buffer, so read-only is OK

	PS4Shader* realShader = (PS4Shader*)o->GetShader();

	int objIndex = realShader->GetConstantBuffer("RenderObjectData");
	int camIndex = realShader->GetConstantBuffer("CameraData");

	Gnm::Sampler trilinearSampler;
	trilinearSampler.init();
	trilinearSampler.setMipFilterMode(Gnm::kMipFilterModeLinear);
	PS4Texture* tex = (PS4Texture*)o->GetTexture(0);
	currentGFXContext->setTextures(Gnm::kShaderStagePs, 0, 1, &tex->GetAPITexture());
	currentGFXContext->setSamplers(Gnm::kShaderStagePs, 0, 1, &trilinearSampler);

	*viewProjMat = mainCamera.BuildProjectionMatrix(1920.0f/1080) * mainCamera.BuildViewMatrix();
	currentGFXContext->setConstantBuffers(Gnm::kShaderStageVs, objIndex, 1, &constantBuffer);
	currentGFXContext->setConstantBuffers(Gnm::kShaderStageVs, camIndex, 1, &cameraBuffer);

	realShader->SubmitShaderSwitch(*currentGFXContext);
	DrawMesh(*((PS4Mesh*)o->GetMesh()));
}

void ExampleRenderer::RenderFrame() {
	UpdateRotationAmount(time);
	defaultShader->SubmitShaderSwitch(*currentGFXContext);

	//Primitive Setup State
	Gnm::PrimitiveSetup primitiveSetup;
	primitiveSetup.init();
	primitiveSetup.setCullFace(Gnm::kPrimitiveSetupCullFaceBack);
	primitiveSetup.setFrontFace(Gnm::kPrimitiveSetupFrontFaceCcw);
	//primitiveSetup.setPolygonMode()
	currentGFXContext->setPrimitiveSetup(primitiveSetup);

	////Screen Access State
	Gnm::DepthStencilControl dsc;
	dsc.init();
	dsc.setDepthControl(Gnm::kDepthControlZWriteEnable, Gnm::kCompareFuncLessEqual);
	dsc.setDepthEnable(true);
	currentGFXContext->setDepthStencilControl(dsc);

	RenderActiveScene();
}