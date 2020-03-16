#pragma once
#include "Transform.h"
#include "CollisionVolume.h"
#include "RenderObject.h"
#include "NetworkObject.h"
#include "Component.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <stdlib.h>

using std::pair;
using std::vector;
using std::unordered_map;

namespace NCL {
	namespace CSC8503 {
		class NetworkObject;

		class GameObject	{
		public:
			GameObject(string name = "");
			~GameObject();
			int playerID;
			virtual void DuringUpdate(float dt);

			template <typename T>
			T getComponent(string name) {
				unordered_map<string, Component*>::const_iterator obj = components.find(name);
				if (obj == components.end())
					return NULL;
				else
					return static_cast<T>(obj->second);
			}

			void addComponent(Component* component) {
				component->setParent(this);
				components.insert(pair<string, Component*>(component->getName(), component));
				component->Start();
			}

			void Update(float dt) {
				DuringUpdate(dt);
				vector<string> todelete;
				for (pair<string, Component*> component : components) {
					component.second->Update(dt);
					if (component.second->toRemove)
						todelete.emplace_back(component.second->getName());
				}
				for (string s : todelete) {
					delete components.at(s);
					components.erase(s);
				}
			}

			void RemoveComponent(string name) {
				unordered_map<string, Component*>::const_iterator obj = components.find(name);
				if (obj != components.end()) {
					delete components.at(obj->first);
					components.erase(obj->first);
				}
			}

			void LateUpdate(float dt) {
				for (pair<string, Component*> component : components) {
					component.second->LateUpdate();
				}
			}

			virtual void Trigger(GameObject& obj);

			void SetBoundingVolume(CollisionVolume* vol) {
				boundingVolume = vol;
			}

			const CollisionVolume* GetBoundingVolume() const {
				return boundingVolume;
			}

			bool IsActive() const {
				return isActive;
			}

			const Transform& GetConstTransform() const {
				return transform;
			}

			Transform& GetTransform() {
				return transform;
			}

			void SetTransform(Transform newTransform) {
				this->transform = newTransform;
			}

			RenderObject* GetRenderObject() const {
				return renderObject;
			}

			NetworkObject* GetNetworkObject() const {
				return networkObject;
			}

			void SetRenderObject(RenderObject* newObject) {
				renderObject = newObject;
			}

			void SetNetworkObject(NetworkObject* newObject) {
				networkObject = newObject;
			}

			const string& GetName() const {
				return name;
			}

			virtual void OnCollisionBegin(GameObject* otherObject) {
				//std::cout << "OnCollisionBegin event occured!\n";
			}

			virtual void OnCollisionEnd(GameObject* otherObject) {
				//std::cout << "OnCollisionEnd event occured!\n";
			}

			unsigned long getLayer() { return layer; };
			unsigned long getLayerMask() { return layerMask; };

			void setLayer(unsigned long l) { layer = l; };
			void setLayerMask(unsigned long m) { layerMask = m; };


			OGLMesh* GetCubeMesh() { return cubeMesh; }
			void SetCubeMesh(OGLMesh* cm) { cubeMesh = cm; }

			OGLMesh* GetPlayerMesh() { return playerMesh; }
			void SetPlayerMesh(OGLMesh* cm) { playerMesh = cm; }

		protected:
			Transform			transform;

			CollisionVolume*	boundingVolume;
			RenderObject*		renderObject;
			NetworkObject*		networkObject;

			OGLMesh* cubeMesh = nullptr;
			OGLMesh* playerMesh = nullptr;

			unsigned long layer; // Bit number
			unsigned long layerMask; // Set bit for each layer that this gameobject should not collide with

			bool	isActive;
			string	name;

			std::unordered_map<string, Component*> components;

			Vector3 broadphaseAABB;

		};
	}
}

