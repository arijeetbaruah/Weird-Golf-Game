#pragma once
#include <unordered_map>
#include "Common/Quaternion.h"
#include "Common/Matrix4.h"
#include "Common/Matrix3.h"
#include "Common/Vector3.h"
#include "Common/Maths.h"
#include <algorithm>
#include <cmath>
#include "Component.h"
#include "Transform.h"

//@Author: David Towers

using namespace NCL::Maths;
using std::unordered_map;
using std::string;
using std::pair;

class GameObject {
public:
	GameObject();
	GameObject(Matrix4 transMatrix);
	GameObject(const GameObject& go);
	GameObject& operator=(GameObject go);
	~GameObject();

	template <typename T>
	T getComponent(string name) {
		return static_cast<T>(components.at(name));
	}

	void addComponent(Component* component);

	void Start();
	void Update();
	void LateUpdate();

private:
	unordered_map<string, Component*> components;
};