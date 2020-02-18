#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"

//@Author: David Towers

using std::shared_ptr;
using std::vector;

class Scene {
private:
	vector<shared_ptr<GameObject>> objects;

public:
	Scene() {

	}

	Scene(const Scene& S) {
		*this = S;
	}

	Scene& operator=(Scene S) {
		for (shared_ptr<GameObject> i : S.objects) {
			objects.emplace_back(i);
		}
		return *this;
	}

	~Scene() {

	}

	void addGameObject(GameObject* go) {
		objects.emplace_back(go);
	}

	void Start() {
		for (shared_ptr<GameObject> i : objects) {
			i->Start();
		}
	}

	void Update() {
		for (shared_ptr<GameObject> i : objects) {
			i->Update();
		}
	}

	void LateUpdate() {
		for (shared_ptr<GameObject> i : objects) {
			i->LateUpdate();
		}
	}
};