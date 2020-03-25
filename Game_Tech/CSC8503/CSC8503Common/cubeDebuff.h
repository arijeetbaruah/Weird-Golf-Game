#pragma once
#include "Timed.h"
#include "GameObject.h"
#include "RenderObject.h"
#include "../GameTech/PhysicsComponent.h"
#include "../GameTech/GameTechRenderer.h"
#include "../GameTech/Player.h"
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
		Player* par;
		RenderObject* ren;
		OGLMesh* Before;
		OGLMesh* After;
		PxMaterial* mat;
		void applyTransformation(Vector3 scale, OGLMesh* mesh, PhysicsComponent* physC);
};

