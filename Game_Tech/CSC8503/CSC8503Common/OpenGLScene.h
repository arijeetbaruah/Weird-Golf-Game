//@Author: Yi Han
#pragma once

#include <vector>
#include "Ray.h"
#include "CollisionDetection.h"
#include "QuadTree.h"
#include"..\..\Common\Matrix4.h"
namespace NCL {
	class Camera;
	using Maths::Ray;

	struct MartixWithID
	{
		Matrix4 currentMatrix;
		int viewMatrixID;
		MartixWithID(Matrix4 newMat, int ID) {
			currentMatrix = newMat;
			viewMatrixID = ID;
		}
		Matrix4 GetViewMatrix() {	return currentMatrix;	}
		void SetMatrix(Matrix4 newMatrix) { currentMatrix = newMatrix; }
	};

	namespace CSC8503 {
		class GameObject;
		class Constraint;

		class OpenGLScene
		{
		protected:
			std::string sceneName;

			vector<GameObject*>		objArray;
			vector<Matrix4>	viewMatrixArray;
			vector<Matrix4>	preMatrixArray;

			int	 objectNum;
			bool isActive;
		private:
			OpenGLScene(std::string sceneName= NULL);
			~OpenGLScene();

			void UpdateViewMatrix(Matrix4 viewMat, int viewID = 0);
			void UpdatePreMatrix(Matrix4 viewMat, int viewID = 0);

			void DrawArray();
			void UpDateArray();
			void DeleteObjectByType(GameObject* object);
			void DeleteObjectByNum(int objectID);
			void AddObject(GameObject* newObject);
			void CleanScene();

			void SetActive(bool newState) { isActive = newState; }

			int GetObjectNum() {		return objectNum;	}
			std::string GetSceneName(){ return sceneName;	}
			bool IsActive() {			return isActive;	}
		};

	}
}