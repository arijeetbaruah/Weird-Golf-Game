#include "Script.h"

void Script::setFunction(std::function<void(GameObject*)> func) {
	this->lambda = func;
}

void Script::nullFunction() {
	lambda = nullptr;
}

void Script::Update() {
	this->lambda(this->getParent());
}

void Script::LateUpdate() {
	this->lambda(this->getParent());
}