/* SIE CONFIDENTIAL
* PlayStation(R)4 Programmer Tool Runtime Library Release 07.008.001
* Copyright (C) 2013 Sony Interactive Entertainment Inc.
*/

#ifndef _SIMPLE_STEREO_PROJECTION_H
#define _SIMPLE_STEREO_PROJECTION_H

#include <vectormath.h>
#include <algorithm>

class SimpleStereoProjection
{
public: // type definition
	typedef sce::Vectormath::Simd::Aos::Vector3 Vector3;
	typedef sce::Vectormath::Simd::Aos::Matrix4 Matrix4;
private: // member variables
	float m_stereo_shift_ratio;
	float m_screen_distance;
	float m_stereo_shift_ratio_max;
	Matrix4 m_projection_matrix_base;
	Matrix4 m_projection_matrix_l;
	Matrix4 m_projection_matrix_r;
private:
	static constexpr float inch_in_cm = 2.54;
	static constexpr float interoculer_distance = 6.3; // length of eye ceparation
public: // constructors and destructors
	SimpleStereoProjection(): m_stereo_shift_ratio(0.0f), m_screen_distance(0.0f), m_stereo_shift_ratio_max(0.0f)
	{
	}
public: // member funcions
	bool SetStereoShiftRatio(float ratio)
	{
		if(ratio < 0.0f)
			return false;
		if(ratio > 1.0f)
			return false;

		m_stereo_shift_ratio = ratio;
		UpdateMatrix();
		return true;
	}
	bool SetScreenDistance(float dist)
	{
		if(dist < 0.0f)
			return false;

		m_screen_distance = dist;
		UpdateMatrix();

		return true;
	}
	bool SetProjectionMatrix(const Matrix4& matrix)
	{
		if(!IsSuitableMatrix(matrix))
			return false;
		m_projection_matrix_base = matrix;
		UpdateMatrix();
		return true;
	}
	bool SetDiagnoralScreenInchSize(float size)
	{
		if(size < 0.0f)
			return false;

		float screen_width = size * inch_in_cm * 16 / sqrt(16*16 + 9*9);
		m_stereo_shift_ratio_max = interoculer_distance / screen_width;

		UpdateMatrix();

		return true;
	}
	Matrix4 GetProjectionMatrixBase()
	{
		return m_projection_matrix_base;
	}
	Matrix4 GetProjectionMatrixLeft() 
	{
		return m_projection_matrix_l;
	}
	Matrix4 GetProjectionMatrixRight() 
	{
		return m_projection_matrix_r;
	}
private:
	void UpdateMatrix() // TODO: implement correct
	{
		if(! IsSuitableMatrix(m_projection_matrix_base))
			return;

		float shift_ratio = std::min(m_stereo_shift_ratio,m_stereo_shift_ratio_max);

		const float m00 = m_projection_matrix_base[0][0];
		const float tanHFoV = (0.0f == m00) ? 0.0 : fabsf(m_projection_matrix_base[2][3]/m00);

		const float a = (tanHFoV > 0.0f) ? shift_ratio : 0.0f;
		const float b = a * m_screen_distance * tanHFoV;

		Matrix4 screen_shift_matrix_l = Matrix4::translation(Vector3(-a,0,0));
		Matrix4 screen_shift_matrix_r = Matrix4::translation(Vector3( a,0,0));
		Matrix4 camera_shift_matrix_l = Matrix4::translation(Vector3( b,0,0));
		Matrix4 camera_shift_matrix_r = Matrix4::translation(Vector3(-b,0,0));

		m_projection_matrix_l = screen_shift_matrix_l
			* m_projection_matrix_base
			* camera_shift_matrix_l;
		m_projection_matrix_r = screen_shift_matrix_r
			* m_projection_matrix_base
			* camera_shift_matrix_r;
	}
	static bool IsSuitableMatrix(const Matrix4& matrix)
	{
		if(matrix[0][1] != 0.0f)return false;
		if(matrix[0][2] != 0.0f)return false;
		if(matrix[0][3] != 0.0f)return false;
		if(matrix[1][0] != 0.0f)return false;
		if(matrix[1][2] != 0.0f)return false;
		if(matrix[1][3] != 0.0f)return false;
		if(matrix[2][0] != 0.0f)return false;
		if(matrix[2][1] != 0.0f)return false;
		if(matrix[3][0] != 0.0f)return false;
		if(matrix[3][1] != 0.0f)return false;
		if(matrix[3][3] != 0.0f)return false;
		if(matrix[2][3] == 0.0f)return false; // should not be zero
		return true;
	}
};

#endif // _SIMPLE_STEREO_PROJECTION_H
