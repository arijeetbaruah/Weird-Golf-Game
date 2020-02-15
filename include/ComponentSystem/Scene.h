#pragma once
#include <vector>
#include "ComponentSystem/GameObject.h"

class Scene {
private:
	std::vector<GameObject*> objects;

public:
	Scene() {

	}

	Scene(const Scene& S) {
		*this = S;
	}

	Scene& operator=(Scene S) {
		for (GameObject* i : S.objects) {
			objects.emplace_back(i);
		}
		return *this;
	}

	~Scene() {
		for (GameObject* i : objects) {
			delete i;
			i = nullptr;
		}
	}

	void addGameObject(GameObject* go) {
		objects.emplace_back(go);
	}

	void Start() {
		for (GameObject* i : objects) {
			i->Start();
		}
	}

	void Update() {
		for (GameObject* i : objects) {
			i->Update();
		}
	}

	void LateUpdate() {
		for (GameObject* i : objects) {
			i->LateUpdate();
		}
	}
};