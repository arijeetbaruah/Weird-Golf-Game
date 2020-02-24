#include "ComponentSystem/GameObject.h"
GameObject::GameObject() {
	Transform* tf = new Transform();
	addComponent(tf);
}

GameObject::GameObject(Matrix4 transMatrix) {
	Transform* tf = new Transform(transMatrix);
	addComponent(tf);
}

GameObject::GameObject(const GameObject& go) {
	*this = go;
}

GameObject& GameObject::operator=(GameObject go) {
	for (pair<string, Component*> i : go.components) {
		components.insert(pair<string, Component*>(i.first, i.second));
	}
	return *this;
}

GameObject::~GameObject() {
	for (pair<string, Component*> i : components) {
		delete i.second;
		i.second = nullptr;
	}
}



void GameObject::addComponent(Component* component) {
	component->setParent(this);
	components.insert(pair<string, Component*>(component->getName(), component));
}

void GameObject::Start() {
	for (std::pair<string, Component*> component : components) {
		component.second->Start();
	}
}

void GameObject::Update() {
	for (std::pair<string, Component*> component : components) {
		component.second->Update();
	}
}

void GameObject::LateUpdate() {
	for (std::pair<string, Component*> component : components) {
		component.second->LateUpdate();
	}
}