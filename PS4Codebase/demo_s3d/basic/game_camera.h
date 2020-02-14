/* SIE CONFIDENTIAL
* PlayStation(R)4 Programmer Tool Runtime Library Release 07.008.001
* Copyright (C) 2013 Sony Interactive Entertainment Inc.
*/

#ifndef _GAME_CAMERA_H
#define _GAME_CAMERA_H

#include <math.h>
#include <vectormath.h>

#define DISTANCE 800.0f

class Camera
{
private:
	/* Gaze target of camera */
	sce::Vectormath::Simd::Aos::Vector3 m_target;

	/* Pitch of camera */
	float m_pitch;
	/* Yaw of camera */
	float m_yaw;
	/* Distance from target */
	float m_distance;

public:
	Camera(void)
	{
		reset();
	}

	/* Rotate the camera around the target */
	void rotate(float horizontal_rad, float vertical_rad)
	{
		m_yaw    += horizontal_rad;
		m_pitch  += vertical_rad;
		if(m_pitch >= M_PI*0.45){
			m_pitch = (float)(M_PI*0.45f);
		}
		if(m_pitch <= -M_PI*0.45){
			m_pitch = -(float)(M_PI*0.45f);
		}
	}

	/* Change the distance from the target */
	void moveDistance(float offset)
	{
		m_distance += offset;
		if(m_distance < 0.001){
			m_distance = 0.001f;
		}

	}

	/* Reset the camera poistion */
	void reset(void)
	{
		m_target      = sce::Vectormath::Simd::Aos::Vector3(0.0f, 80.0f, 0.0f);

		m_yaw   = 0.0f;
		m_pitch = (float)(0.0 / 180.0 * M_PI);
		m_distance = DISTANCE;
	}

	/* Parallel move the camera position and target */
	void parallelMove(float horizontal_offset, float vertical_offset)
	{
		sce::Vectormath::Simd::Aos::Vector3 position = getPosition();
		sce::Vectormath::Simd::Aos::Vector3 y        = sce::Vectormath::Simd::Aos::Vector3(0, 1, 0);
		sce::Vectormath::Simd::Aos::Vector3 front    = normalize(m_target - position);
		sce::Vectormath::Simd::Aos::Vector3 up       = normalize(y - dot(y, front) * front);
		sce::Vectormath::Simd::Aos::Vector3 right    = cross(front, up);

		m_target += vertical_offset * up + horizontal_offset * right;
	}

	/* Return the camear position */
	sce::Vectormath::Simd::Aos::Vector3 getPosition(void)
	{
		sce::Vectormath::Simd::Aos::Vector3 z = sce::Vectormath::Simd::Aos::Vector3(0.0f, 0.0f, -1.0f);
		sce::Vectormath::Simd::Aos::Vector3 orientation = 
			(sce::Vectormath::Simd::Aos::Matrix4::rotationY(-m_yaw) 
			* sce::Vectormath::Simd::Aos::Matrix4::rotationX(-m_pitch) 
			* sce::Vectormath::Simd::Aos::Vector4(z, 1.0)).getXYZ();
		return m_target - m_distance * orientation;
	}

	/* Return the view matrix of this camera */
	sce::Vectormath::Simd::Aos::Matrix4 getViewMatrix(void)
	{
		return sce::Vectormath::Simd::Aos::Matrix4::lookAt(
			sce::Vectormath::Simd::Aos::Point3(getPosition()),
			sce::Vectormath::Simd::Aos::Point3(m_target),
			sce::Vectormath::Simd::Aos::Vector3(0.0f, 1.0f, 0.0f));
	}
};




#endif /* _GAME_CAMERA_H */


