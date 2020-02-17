#pragma once
#include <unordered_map>
#include "Common/Quaternion.h"
#include "Common/Matrix4.h"
#include "Common/Matrix3.h"
#include "Common/Vector3.h"
#include "Common/Maths.h"
#include <algorithm>
#include <cmath>
#include "ComponentSystem/Component.h"
#include "ComponentSystem/Transform.h"

using namespace NCL::Maths;

class GameObject {
public:
	GameObject() {
		Transform* tf = new Transform();
		addComponent(tf);
	}

	GameObject(Matrix4 transMatrix) {
		Transform* tf = new Transform(transMatrix);
		addComponent(tf);
	}

	GameObject(const GameObject& go) {
		*this = go;
	}

	GameObject& operator=(GameObject go) {
		for (std::pair<std::string, Component*> i : go.components) {
			components.insert(std::pair<std::string, Component*>(i.first, i.second));
		}
		return *this;
	}

	~GameObject() {
		for (std::pair<std::string, Component*> i : components) {
			delete i.second;
			i.second = nullptr;
		}
	}


	Component* getComponent(std::string name) {
		return components.at(name);
	}

	void addComponent(Component* component) {
		components.insert(std::pair<std::string, Component*>(component->getName(), component));
	}

	void Start() {
		for (std::pair<std::string, Component*> component : components) {
			component.second->Start();
		}
	}

	void Update() {
		for (std::pair<std::string, Component*> component : components) {
			component.second->Update();
		}
	}

	void LateUpdate() {
		for (std::pair<std::string, Component*> component : components) {
			component.second->LateUpdate();
		}
	}

private:
	std::unordered_map<std::string, Component*> components;
};