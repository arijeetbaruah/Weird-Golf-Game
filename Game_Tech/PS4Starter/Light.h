#pragma once

#include "../Common/Vector3.h"
#include "../Common/Vector4.h"

using NCL::Maths::Vector3;
using NCL::Maths::Vector4;

namespace NCL
{
	class Light
	{
	public:
		Light(Vector3 position = Vector3(0, 0, 0),
			Vector4 color = Vector4(1, 1, 1, 1),
			float radius = 100,
			float intensity = 0.5) :
			position(position),
			color(color),
			radius(radius),
			intensity(intensity)
		{

		}

		~Light()
		{

		}

		Vector3 GetPosition() const
		{
			return position;
		}
		void SetPosition(Vector3 val)
		{
			position = val;
		}

		float GetRadius() const
		{
			return radius;
		}
		void SetRadius(float val)
		{
			radius = val;
		}

		Vector4 GetColor() const
		{
			return color;
		}
		void SetColor(Vector4 val)
		{
			color = val;
		}

		float GetIntensity() const
		{
			return intensity;
		}
		void SetIntensity(float val)
		{
			intensity = val;
		}


	protected:
		Vector3 position;
		Vector4 color;
		float radius;
		float intensity;
	};
}

