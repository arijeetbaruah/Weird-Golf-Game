#include "Component.h"
using namespace NCL;
using namespace CSC8503;
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

void Component::setParent(GameObject* go) {
	parent = go;
}

GameObject* Component::getParent() {
	return parent;
}
