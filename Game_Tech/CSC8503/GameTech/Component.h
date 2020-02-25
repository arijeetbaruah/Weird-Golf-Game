#pragma once
#include <string>

//@Author: David Towers

//class GameObject;
class Component {
private:
	std::string name;
	//GameObject* parent;

public:
	Component();
	Component(std::string name);
	virtual ~Component() {};

	std::string getName();
	void setName(std::string name);

	virtual void Start();
	virtual void Update() = 0;
	virtual void LateUpdate();

	//void setParent(GameObject* go);
	//GameObject* getParent();
};


