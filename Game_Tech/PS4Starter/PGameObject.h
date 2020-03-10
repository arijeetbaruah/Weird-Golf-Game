#pragma once
#include <iostream>
#include"RenderObject.h"
#pragma once
#include "../Common/Matrix4.h"


namespace NCL {
	namespace PS4 {
		class PGameObject
		{
		public:
			PGameObject(std::string objectName);
			~PGameObject();

			bool IsActive() const {
				return isActive;
			}

			const Maths::Matrix4& GetTransform() const {
				return transform;
			}

			void SetTransform(Maths::Matrix4 newTransform) {
				this->transform = newTransform;
			}

			RenderObject* GetRenderObject() const {
				return renderObject;
			}

			void SetRenderObject(RenderObject* newObject) {
				renderObject = newObject;
			}

			const std::string& GetName() const {
				return name;
			}

		protected:
			Maths::Matrix4		transform;
			RenderObject*		renderObject;
			bool				isActive;
			std::string			name;
		};
	}
}
