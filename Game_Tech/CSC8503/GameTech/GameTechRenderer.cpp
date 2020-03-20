#include "GameTechRenderer.h"
#include "../CSC8503Common/GameObject.h"
#include "../../Common/Camera.h"
#include "../../Common/Vector2.h"
#include "../../Common/Vector3.h"
using namespace NCL;
using namespace Rendering;
using namespace CSC8503;

#define SHADOWSIZE 4096

#ifdef _ORBIS
//PS4 code
#else 




Matrix4 biasMatrix = Matrix4::Translation(Vector3(0.5, 0.5, 0.5)) * Matrix4::Scale(Vector3(0.5, 0.5, 0.5));

GameTechRenderer::GameTechRenderer(GameWorld& world) : OGLRenderer(*Window::GetWindow()), gameWorld(world)	{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shadowShader = new OGLShader("GameTechShadowVert.glsl", "GameTechShadowFrag.glsl");
	skyboxShader = new OGLShader("SkyboxVertex.glsl", "SkyboxFragment.glsl");
	OcclusionShader = new OGLShader("OcclusionVertex.glsl", "OcclusionFragment.glsl");

	glGenTextures(1, &shadowTex);
	glBindTexture(GL_TEXTURE_2D, shadowTex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
			     SHADOWSIZE, SHADOWSIZE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &shadowFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D, shadowTex, 0);
	glDrawBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(1, 1, 1, 1);

	//Set up the light properties
	lightColour = Vector4(0.8f, 0.8f, 0.5f, 1.0f);
	lightRadius = 1000.0f;
	lightPosition = Vector3(-200.0f, 60.0f, -200.0f);

	std::vector<std::string> textures = 
	{
		SKYBOX_TEXTURES
	};
	skyboxTex = LoadSkyBox(textures);

	quad = new OGLMesh();
	
	quad->SetVertexIndices({0, 1, 2, 3});
	quad->SetPrimitiveType(NCL::GeometryPrimitive::TriangleStrip);
	quad->SetVertexPositions({Vector3(-1.0f, -1.0f, 0.0f), 
		Vector3(-1.0f, 1.0f, 0.0f), 
		Vector3(1.0f, -1.0f, 0.0f), 
		Vector3(1.0f, 1.0f, 0.0f)});

	quad->SetVertexTextureCoords({Vector2(0.0f, 1.0f), 
		Vector2(0.0f, 0.0f), 
		Vector2(1.0f, 1.0f), 
		Vector2(1.0f, 0.0f)});
	quad->UploadToGPU();
}

GameTechRenderer::~GameTechRenderer()	{
	glDeleteTextures(1, &shadowTex);
	glDeleteFramebuffers(1, &shadowFBO);
	glDeleteTextures(1, &skyboxTex);
	delete shadowShader;
	delete skyboxShader;
	delete quad;
}

void GameTechRenderer::RenderFrame() {
	glEnable(GL_CULL_FACE);
	glClearColor(0, 0.41, 0.58, 1);
	DrawSkyBox();
	BuildObjectList();
	SortObjectList();
	RenderShadowMap();
	RenderCamera();
	DrawOcclusion();
	glDisable(GL_CULL_FACE); //Todo - text indices are going the wrong way...
}

void GameTechRenderer::BuildObjectList() {
	std::vector<GameObject*>::const_iterator first;
	std::vector<GameObject*>::const_iterator last;

	gameWorld.GetObjectIterators(first, last);

	activeObjects.clear();

	for (std::vector<GameObject*>::const_iterator i = first; i != last; ++i) {
		if ((*i)->IsActive()) {
			const RenderObject*g = (*i)->GetRenderObject();
			if (g) {
				activeObjects.emplace_back(g);
			}
		}
	}
}

void GameTechRenderer::SortObjectList() {

}

void GameTechRenderer::RenderShadowMap() {
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glViewport(0, 0, SHADOWSIZE, SHADOWSIZE);

	glCullFace(GL_FRONT);

	BindShader(shadowShader);
	int mvpLocation = glGetUniformLocation(shadowShader->GetProgramID(), "mvpMatrix");

	Matrix4 shadowViewMatrix = Matrix4::BuildViewMatrix(lightPosition, Vector3(0, 0, 0), Vector3(0,1,0));
	Matrix4 shadowProjMatrix = Matrix4::Perspective(100.0f, 500.0f, 1, 45.0f);

	Matrix4 mvMatrix = shadowProjMatrix * shadowViewMatrix;

	shadowMatrix = biasMatrix * mvMatrix; //we'll use this one later on

	for (const auto&i : activeObjects) {
		Matrix4 modelMatrix = (*i).GetTransform()->GetWorldMatrix();
		Matrix4 mvpMatrix	= mvMatrix * modelMatrix;
		glUniformMatrix4fv(mvpLocation, 1, false, (float*)&mvpMatrix);
		BindMesh((*i).GetMesh());
		DrawBoundMesh();


	}

	glViewport(0, 0, currentWidth, currentHeight);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glCullFace(GL_BACK);
}

void GameTechRenderer::RenderCamera() {
	float screenAspect = (float)currentWidth / (float)currentHeight;
	Matrix4 viewMatrix = gameWorld.GetMainCamera()->BuildViewMatrix();
	Matrix4 projMatrix = gameWorld.GetMainCamera()->BuildProjectionMatrix(screenAspect);

	OGLShader* activeShader = nullptr;
	int projLocation	= 0;
	int viewLocation	= 0;
	int modelLocation	= 0;
	int colourLocation  = 0;
	int hasVColLocation = 0;
	int hasTexLocation  = 0;
	int shadowLocation  = 0;

	int lightPosLocation	= 0;
	int lightColourLocation = 0;
	int lightRadiusLocation = 0;

	int cameraLocation = 0;

	//TODO - PUT IN FUNCTION
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, shadowTex);

	for (const auto&i : activeObjects) {
		OGLShader* shader = (OGLShader*)(*i).GetShader();
		BindShader(shader);

		BindTextureToShader((OGLTexture*)(*i).GetDefaultTexture(), "mainTex", 0);

		if (activeShader != shader) {
			projLocation	= glGetUniformLocation(shader->GetProgramID(), "projMatrix");
			viewLocation	= glGetUniformLocation(shader->GetProgramID(), "viewMatrix");
			modelLocation	= glGetUniformLocation(shader->GetProgramID(), "modelMatrix");
			shadowLocation  = glGetUniformLocation(shader->GetProgramID(), "shadowMatrix");
			colourLocation  = glGetUniformLocation(shader->GetProgramID(), "objectColour");
			hasVColLocation = glGetUniformLocation(shader->GetProgramID(), "hasVertexColours");
			hasTexLocation  = glGetUniformLocation(shader->GetProgramID(), "hasTexture");

			lightPosLocation	= glGetUniformLocation(shader->GetProgramID(), "lightPos");
			lightColourLocation = glGetUniformLocation(shader->GetProgramID(), "lightColour");
			lightRadiusLocation = glGetUniformLocation(shader->GetProgramID(), "lightRadius");

			cameraLocation = glGetUniformLocation(shader->GetProgramID(), "cameraPos");
			glUniform3fv(cameraLocation, 1, (float*)&gameWorld.GetMainCamera()->GetPosition());

			glUniformMatrix4fv(projLocation, 1, false, (float*)&projMatrix);
			glUniformMatrix4fv(viewLocation, 1, false, (float*)&viewMatrix);

			glUniform3fv(lightPosLocation	, 1, (float*)&lightPosition);
			glUniform4fv(lightColourLocation, 1, (float*)&lightColour);
			glUniform1f(lightRadiusLocation , lightRadius);

			int shadowTexLocation = glGetUniformLocation(shader->GetProgramID(), "shadowTex");
			glUniform1i(shadowTexLocation, 1);

			activeShader = shader;
		}

		Matrix4 modelMatrix = (*i).GetTransform()->GetWorldMatrix();
		glUniformMatrix4fv(modelLocation, 1, false, (float*)&modelMatrix);			
		
		Matrix4 fullShadowMat = shadowMatrix * modelMatrix;
		glUniformMatrix4fv(shadowLocation, 1, false, (float*)&fullShadowMat);

		glUniform4fv(colourLocation, 1, (float*)&i->GetColour());

		//glUniform1i(hasVColLocation, !(*i).GetMesh()->GetColourData().empty());

		//glUniform1i(hasTexLocation, (OGLTexture*)(*i).GetDefaultTexture() ? 1:0);

		glUniform1i(hasVColLocation, !(*i).GetMesh()->GetColourData().empty());

		glUniform1i(hasTexLocation, (OGLTexture*)(*i).GetDefaultTexture() ? 1 : 0);

		BindMesh((*i).GetMesh());
		DrawBoundMesh();

	}
}

void GameTechRenderer::SetupDebugMatrix(OGLShader*s) {
	float screenAspect = (float)currentWidth / (float)currentHeight;
	Matrix4 viewMatrix = gameWorld.GetMainCamera()->BuildViewMatrix();
	Matrix4 projMatrix = gameWorld.GetMainCamera()->BuildProjectionMatrix(screenAspect);

	Matrix4 vp = projMatrix * viewMatrix;

	int matLocation = glGetUniformLocation(s->GetProgramID(), "viewProjMatrix");

	glUniformMatrix4fv(matLocation, 1, false, (float*)&vp);
}

GLuint GameTechRenderer::LoadSkyBox(const std::vector<std::string>& textures)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		unsigned char* data = stbi_load(textures[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Invalid Texture path: " << textures[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

void GameTechRenderer::DrawSkyBox()
{
	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);
	BindShader(skyboxShader);
	offsetX += SKY_BOX_ROTATION_SPEED;
	int cubeTexNightIndex = glGetUniformLocation(skyboxShader->GetProgramID(), "cubeTexNight");
	int cameraPosIndex = glGetUniformLocation(skyboxShader->GetProgramID(), "cameraPos");
	int offsetXIndex = glGetUniformLocation(skyboxShader->GetProgramID(), "offsetX");
	int projMatrixIndex = glGetUniformLocation(skyboxShader->GetProgramID(), "projMatrix");
	int viewMatrixIndex = glGetUniformLocation(skyboxShader->GetProgramID(), "viewMatrix");

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);

	glUniform1i(cubeTexNightIndex, 0);
	glUniform1f(offsetXIndex, offsetX);
	glUniform3fv(cameraPosIndex, 1, (float*)&gameWorld.GetMainCamera()->GetPosition());
	glUniformMatrix4fv(projMatrixIndex, 1, false, (float*)&Matrix4::Perspective(0, 10000, 1920/1080, 120));
	glUniformMatrix4fv(viewMatrixIndex, 1, false, (float*)&gameWorld.GetMainCamera()->BuildViewMatrix());

	BindMesh(quad);
	DrawBoundMesh();

	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
}

void GameTechRenderer::DrawOcclusion()
{
	if (ballObject == nullptr)
	{
		return;
	}
	glDepthFunc(GL_GREATER);
	BindShader(OcclusionShader);

	float screenAspect = (float)currentWidth / (float)currentHeight;

	GLuint projLocation = glGetUniformLocation(OcclusionShader->GetProgramID(), "projMatrix");
	GLuint viewLocation = glGetUniformLocation(OcclusionShader->GetProgramID(), "viewMatrix");
	GLuint modelLocation = glGetUniformLocation(OcclusionShader->GetProgramID(), "modelMatrix");

	Matrix4 viewMatrix = gameWorld.GetMainCamera()->BuildViewMatrix();
	Matrix4 projMatrix = gameWorld.GetMainCamera()->BuildProjectionMatrix(screenAspect);
	Matrix4 modelMatrix = ballObject->GetTransform().GetWorldMatrix();

	glUniformMatrix4fv(projLocation, 1, false, (float*)&projMatrix);
	glUniformMatrix4fv(viewLocation, 1, false, (float*)&viewMatrix);
	glUniformMatrix4fv(modelLocation, 1, false, (float*)&modelMatrix);

	BindMesh(ballObject->GetRenderObject()->GetMesh());
	DrawBoundMesh();
	glDepthFunc(GL_LESS);
}
#endif