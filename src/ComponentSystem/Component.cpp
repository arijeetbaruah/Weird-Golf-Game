#include "ComponentSystem/Component.h"

Component::Component() {
	this->name = "";
}

Component::Component(std::string name) {
	this->name = name;
}

std::string Component::getName() {
	return name;
}
void Component::setName(std::string name) {
	this->name = name;
}

void Component::Start() {}

void Component::Update() {}

void Component::LateUpdate() {}
