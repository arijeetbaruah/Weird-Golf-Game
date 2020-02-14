/* SIE CONFIDENTIAL
* PlayStation(R)4 Programmer Tool Runtime Library Release 07.008.001
* Copyright (C) 2013 Sony Interactive Entertainment Inc.
*/

#include <stdio.h>

extern "C" size_t sceLibcHeapSize = 256 * 1024 * 1024;

#include <sampleutil.h>
#include <vectormath.h>
#include <vector>
#include <string>
#include "game_camera.h"
#include "simple_stereo_projection.h"
#include <scebase_common.h>
#include <video_out.h>
#include <pad.h>

#define APP_DIR "/app0/data/"

namespace vecmath = sce::Vectormath::Simd::Aos;
namespace ssg = sce::SampleUtil::Graphics;
namespace ssi = sce::SampleUtil::Input;
namespace ssa = sce::SampleUtil::Audio;

class Character
{
private:
	ssg::Collada::ColladaData     *m_collada;
	ssg::Collada::InstanceVisualScene *m_instanceVisualScene;
	ssg::Collada::AnimationPlayer		*m_animPlayer;
public:
	vecmath::Vector3 m_pos;
	float m_duckRotY;

	float m_animationTime;


	int initialize(ssg::Collada::ColladaLoader *loader, const char* path)
	{
		int ret;
		ret = loader->load(&m_collada, path);
		if(ret != SCE_OK){
			printf("Error: loading \"%s\" failed.\n", path);
		}
		assert(ret == SCE_OK);
		printf("path=%s\n", path);
		ret = ssg::Collada::createInstanceVisualScene(&m_instanceVisualScene, m_collada->getVisualScene());
		assert(ret == SCE_OK);

		ret = ssg::Collada::createAnimationPlayer(&m_animPlayer, m_instanceVisualScene, m_collada->getAnimation());
		SCE_SAMPLE_UTIL_ASSERT_EQUAL(ret, SCE_OK);

		m_animPlayer->setTime(0.0f);

		m_pos = vecmath::Vector3(0, 0, 0);
		m_duckRotY = 0.0f;

		m_animationTime = 0.0f;
		scePadInit();
		return SCE_OK;
	}

	int finalize(void)
	{
		sce::SampleUtil::destroy(m_animPlayer);
		sce::SampleUtil::destroy(m_instanceVisualScene);
		sce::SampleUtil::destroy(m_collada);
		return SCE_OK;
	}

	void update(void)
	{
		m_animPlayer->setTime(m_animationTime);
		m_animationTime += 0.01f;
		if(m_animationTime >= m_animPlayer->getAnimation()->getEndTime()){
			m_animationTime= 0.0f;
		}

		m_duckRotY += 0.01f;
		if(m_duckRotY >= 2.0f * M_PI){
			m_duckRotY -= 2.0f * M_PI;
		}

	}


	vecmath::Matrix4 getMatrix(void) const
	{
		return vecmath::Matrix4::translation(m_pos) 
			* vecmath::Matrix4::rotationZYX(vecmath::Vector3(0.0, m_duckRotY, 0.0f));
	}

	void draw(ssg::GraphicsContext *context)
	{
		m_instanceVisualScene->draw(context, getMatrix());
	}
};







class Application : public sce::SampleUtil::SampleSkeleton
{
private:
	enum DrawTarget
	{
		kDrawTargetNormal,
		kDrawTargetS3DLeft,
		kDrawTargetS3DRight
	};
private:
	ssg::SpriteRenderer *m_sprite;

	ssg::Collada::ColladaLoader       *m_loader;
	Camera m_camera;
	SimpleStereoProjection m_stereo_projection;

	Character m_duck;
	Character m_boy;
	Character m_gun;
	Character m_heart;
	Character m_level;

	uint32_t m_numFrames;

	bool m_is_output_s3d;
	int  m_display_width;
	int  m_display_height;

public:
	virtual int initialize(void)
	{
		int ret;
		(void)ret;
		
		m_is_output_s3d = false;

		SampleSkeletonOption sample_skelton_option;
		sce::SampleUtil::Graphics::GraphicsContextOption graphics_option;
		sample_skelton_option.graphicsOption = &graphics_option;
		graphics_option.enableS3dView = true;

		ret = initializeUtil(kFunctionFlagAll, -1, -1, &sample_skelton_option);
		assert(ret == SCE_OK);

		// Check display 3D capability and switch to 3D
		if(getGraphicsContext()->isDisplaymodeSupported(getGraphicsContext()->kDisplayModeS3dView))
		{
			ret = getGraphicsContext()->setDisplaymode(getGraphicsContext()->kDisplayModeS3dView);
			assert(ret >= 0);
			m_is_output_s3d = true;
		}

		sce::SampleUtil::Graphics::RenderTarget* render_target = getGraphicsContext()->getNextRenderTarget();
		m_display_width  = render_target->getWidth();
		m_display_height = render_target->getHeight();
		printf("RenderTargetSize = (%4d, %4d)\n", m_display_width, m_display_height);

		m_sprite = NULL;
		ssg::createSpriteRenderer(&m_sprite, getGraphicsContext());
		m_sprite->setRenderTargetSize(vecmath::Vector2(m_display_width, m_display_height));

		ssg::Collada::createColladaLoader(&m_loader, getGraphicsContext());

		m_camera.reset();

		const float fov    = (float)(M_PI/6.0f);
		const float aspect = (float)m_display_width / (float)m_display_height;
		const float _near   = 0.1f;
		const float _far    = 10000.0f;
		vecmath::Matrix4 projectionMatrix = vecmath::Matrix4::perspective(fov,  aspect, _near, _far);

		vecmath::Vector3 lightPos(0,1200, 1000);
		vecmath::Vector3 lightColor(1.0, 1.0, 1.0);
		m_loader->getDefaultParams()->setLight(lightPos, lightColor);
		m_loader->getDefaultParams()->setViewMatrix(m_camera.getViewMatrix());
		m_loader->getDefaultParams()->setProjectionMatrix(projectionMatrix);

		// Get Screen Size in Inchs
		int screen_size = 40; // default is 40
		sce::SampleUtil::Graphics::Gnm::GraphicsContextGnm *contextGnm = 
			sce::SampleUtil::Graphics::Gnm::GraphicsContextGnm::cast(getGraphicsContext());
		SceVideoOutResolutionStatus videoStatus;
		if((ret = sceVideoOutGetResolutionStatus(contextGnm->getVideoOutHandle(),&videoStatus))==0)
		{
			screen_size = videoStatus.screenSizeInInch;
			printf("Screen size = %d\n",screen_size);
			assert((10 <= screen_size) && (screen_size <= 1000));
		}
		else
		{
			printf("Error!sceVideoOutGetResolutionStatus() == %08X\n",ret);
		}

		m_stereo_projection.SetProjectionMatrix(projectionMatrix);
		m_stereo_projection.SetScreenDistance(700.f); // objects at arround 800 in the depth direction.
		m_stereo_projection.SetStereoShiftRatio(0.03f);
		m_stereo_projection.SetDiagnoralScreenInchSize(screen_size);

		m_duck.initialize(m_loader, APP_DIR "graphics/model/duck/duck.dae");
		m_boy.initialize(m_loader, APP_DIR "graphics/model/boy/astroBoy_walk.dae");
		m_gun.initialize(m_loader, APP_DIR"graphics/model/BigGun/Gun.dae");
		m_heart.initialize(m_loader, APP_DIR"graphics/model/Heart/heart.dae");
		m_level.initialize(m_loader, APP_DIR"graphics/model/Level/TestLevel.dae");

		m_duck.m_pos = vecmath::Vector3(100, 0, 0);
		m_boy.m_pos = vecmath::Vector3(-100, 0, 0);
		m_gun.m_pos = vecmath::Vector3(0, 0, 0);
		m_heart.m_pos = vecmath::Vector3(0, 100, 0);
		m_level.m_pos = vecmath::Vector3(0, 0, 100);

		m_numFrames = 0;

		return SCE_OK;
	}
	virtual int update(void)
	{
		int ret;
		(void)ret;

		ret = updateUtil();
		assert(ret == SCE_OK);

		m_numFrames ++;

		m_boy.update();
		m_duck.update();
		m_gun.update();
		m_heart.update();
		m_level.update();

		return SCE_OK;
	}	

	void drawRects(void)
	{
		uint32_t rectWidthInPix = 0.04 * m_display_height;
		uint32_t rectHeightInPix = 0.06 * m_display_height;
		vecmath::Vector2 rectSize = vecmath::divPerElem(vecmath::Vector2(rectWidthInPix, rectHeightInPix),
			                               vecmath::Vector2(m_display_width, m_display_height));

		uint32_t paddingInPix = 0.04 * m_display_height;

		uint32_t stride = rectWidthInPix + paddingInPix;
		int32_t n = m_display_width / stride;
		
		for(int32_t i=-2; i<n+2; i++){
			int32_t posX = (rectWidthInPix + paddingInPix) * i - (m_numFrames%32) * stride / 32;
			vecmath::Vector2 rectPosInPix( posX, 0.01 * m_display_height);
			vecmath::Vector2 rectPosInPix2( posX, m_display_height - 0.01 * m_display_height - rectHeightInPix);

			vecmath::Vector2 rectPos = divPerElem(rectPosInPix, vecmath::Vector2(m_display_width, m_display_height));
			vecmath::Vector2 rectPos2 = divPerElem(rectPosInPix2, vecmath::Vector2(m_display_width, m_display_height));

			m_sprite->fillRect(getGraphicsContext(),	rectPos, rectSize,		vecmath::Vector4(1.0f));
			m_sprite->fillRect(getGraphicsContext(),	rectPos2, rectSize,		vecmath::Vector4(1.0f));
		}

	}

	virtual void render(void)
	{
		if(m_is_output_s3d)
		{
			renderEachField(kDrawTargetS3DLeft);
			renderEachField(kDrawTargetS3DRight);
		}
		else
			renderEachField(kDrawTargetNormal);
		getGraphicsContext()->flip( 1);
	}
	void renderEachField(DrawTarget side)
	{
		switch(side)
		{
		case kDrawTargetS3DLeft:
			m_loader->getDefaultParams()->setProjectionMatrix(m_stereo_projection.GetProjectionMatrixLeft());
			break;
		case kDrawTargetS3DRight:
			m_loader->getDefaultParams()->setProjectionMatrix(m_stereo_projection.GetProjectionMatrixRight());
			break;
		default:
			printf("renderEachField:[argument error]\n");
			/* fall through */
		case kDrawTargetNormal:
			m_loader->getDefaultParams()->setProjectionMatrix(m_stereo_projection.GetProjectionMatrixBase());
			break;
		}

		getGraphicsContext()->beginScene(getGraphicsContext()->getNextRenderTarget((side != kDrawTargetS3DRight) ? ssg::GraphicsContext::kFrameBufferSideLeft : ssg::GraphicsContext::kFrameBufferSideRight),
			                             getGraphicsContext()->getDepthStencilSurface());

		getGraphicsContext()->clearRenderTarget(0x00000000);

		getGraphicsContext()->setDepthWriteEnable(true);
		getGraphicsContext()->setDepthFunc(ssg::kDepthFuncLessEqual);
		// drawRects();

		m_loader->getDefaultParams()->setViewMatrix(m_camera.getViewMatrix());
		getGraphicsContext()->setCullMode(ssg::kCullNone);
		m_duck.draw(getGraphicsContext());
		m_boy.draw(getGraphicsContext());
		m_gun.draw(getGraphicsContext());
		m_heart.draw(getGraphicsContext());
		m_level.draw(getGraphicsContext());
		getGraphicsContext()->setDepthFunc(ssg::kDepthFuncAlways);
		// m_sprite->drawDebugStringf(getGraphicsContext(), vecmath::Vector2(0.103, 0.103), 0.08, vecmath::Vector4(0.3, 0.3, 0.3, 0.7), "S3D BASIC DEMO");
		// m_sprite->drawDebugStringf(getGraphicsContext(), vecmath::Vector2(0.1, 0.1), 0.08, vecmath::Vector4(1.0, 0.3, 0.0, 1.0), "S3D BASIC DEMO");

		m_sprite->drawDebugStringf(getGraphicsContext(), vecmath::Vector2(0.80, 0.15), 0.03, vecmath::Vector4(1.0f), "3D Out: %s", (m_is_output_s3d)? "On": "Off");

		getGraphicsContext()->endScene();
	}
	virtual int finalize(void)
	{
		int ret;
		(void)ret;
		m_duck.finalize();
		m_boy.finalize();
		m_gun.finalize();
		m_heart.finalize();
		m_level.finalize();
		sce::SampleUtil::destroy(m_loader);
		sce::SampleUtil::destroy(m_sprite);
		m_sprite = NULL;
		ret = finalizeUtil();
		assert(ret == SCE_OK);
		return SCE_OK;
	}
};

Application g_application;


int main(void)
{
	int ret = 0;
	ret = g_application.initialize();
	assert(ret == SCE_OK);

	while(1){
		ret = g_application.update();
		if(ret != SCE_OK){
			break;
		}
		assert(ret == SCE_OK);

		g_application.render();
	}

	ret = g_application.finalize();
	assert(ret == SCE_OK);

	return 0;
}

