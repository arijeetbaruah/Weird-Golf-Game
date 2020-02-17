#pragma once
#include <string>

class Component {
	private:
		std::string name;

public:
	Component();
	Component(std::string name);
	virtual ~Component() = 0;

	std::string getName();
	void setName(std::string name);

	virtual void Start();

	virtual void Update();

	virtual void LateUpdate();
};

