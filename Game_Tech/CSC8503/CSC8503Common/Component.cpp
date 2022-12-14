#include "Component.h"

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

void Component::Update(float dt) {}

void Component::LateUpdate() {}

void Component::setParent(GameObject* go) {
	parent = go;
}

GameObject* Component::getParent() {
	return parent;
}
