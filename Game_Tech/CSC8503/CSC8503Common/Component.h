#pragma once
//#include "GameObject.h"
#include <string>

//@Author: David Towers
namespace NCL {
	namespace CSC8503 {
		class GameObject;
	}
}

using namespace NCL;
using namespace CSC8503;
class Component {
private:
	std::string name;
	GameObject* parent;

public:
	Component();
	Component(std::string name);
	virtual ~Component() {};

	std::string getName();
	void setName(std::string name);

	virtual void Start();
	virtual void Update(float dt) = 0;
	virtual void LateUpdate();

	void setParent(GameObject* go);
	GameObject* getParent();

	bool toRemove = false;
};


