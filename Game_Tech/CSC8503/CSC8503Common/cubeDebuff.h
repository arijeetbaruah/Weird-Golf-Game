#pragma once
#include "Timed.h"
#include "GameObject.h"
#include "RenderObject.h"
#include "../GameTech/GameTechRenderer.h"
namespace NCL {
	namespace CSC8503 {
		class GameObject;
		class RenderObject;
		class TutorialGame;
	}
}

class cubeDebuff : public Timed {
	public:
		cubeDebuff(OGLMesh* before, OGLMesh* after);

		void Apply();
		void Remove();
		void Start();
	protected:
		GameObject* par;
		RenderObject* ren;
		OGLMesh* Before;
		OGLMesh* After;
};

