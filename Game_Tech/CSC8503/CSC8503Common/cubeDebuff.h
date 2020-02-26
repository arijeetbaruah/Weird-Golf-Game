#pragma once
#include "Timed.h"
#include "GameObject.h"
#include "RenderObject.h"
namespace NCL {
	namespace CSC8503 {
		class GameObject;
		class RenderObject;
		class TutorialGame;
	}
}
class TutorialGame;

class cubeDebuff : public Timed {
	public:
		cubeDebuff();

		void Apply();
		void Remove();
		void Start();
	protected:
		GameObject* par;
		RenderObject* ren;
};

