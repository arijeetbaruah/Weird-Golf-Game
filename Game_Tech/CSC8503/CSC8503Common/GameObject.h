#pragma once
#include "Transform.h"
#include "CollisionVolume.h"

#include "PhysicsObject.h"
#include "RenderObject.h"
#include "NetworkObject.h"
#include "Component.h"

#include <iostream>
#include <unordered_map>
#include <vector>

using std::pair;
using std::vector;

namespace NCL {
	namespace CSC8503 {
		class NetworkObject;

		class GameObject	{
		public:
			GameObject(string name = "");
			~GameObject();

			virtual void DuringUpdate(float dt);

			template <typename T>
			T getComponent(string name) {
				return static_cast<T>(components.at(name));
			}

			void addComponent(Component* component) {
				component->setParent(this);
				components.insert(pair<string, Component*>(component->getName(), component));
				component->Start();
			}
			void removeComponent(string name) {
				Component* toRemove = components.at(name);
				components.erase(name);
				delete toRemove;
			}
			void Update(float dt) {
				DuringUpdate(dt);
				for (pair<string, Component*> component : components) {
					component.second->Update(dt);
				}
				for (pair<string, Component*> component : components) {
					if (component.second->toRemove)
						removeComponent(component.second->getName());
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

			RenderObject* GetRenderObject() const {
				return renderObject;
			}

			PhysicsObject* GetPhysicsObject() const {
				return physicsObject;
			}

			NetworkObject* GetNetworkObject() const {
				return networkObject;
			}

			void SetRenderObject(RenderObject* newObject) {
				renderObject = newObject;
			}

			void SetPhysicsObject(PhysicsObject* newObject) {
				physicsObject = newObject;
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

			bool GetBroadphaseAABB(Vector3&outsize) const;

			void UpdateBroadphaseAABB();

			unsigned long getLayer() { return layer; };
			unsigned long getLayerMask() { return layerMask; };

			void setLayer(unsigned long l) { layer = l; };
			void setLayerMask(unsigned long m) { layerMask = m; };

		protected:
			Transform			transform;

			CollisionVolume*	boundingVolume;
			PhysicsObject*		physicsObject;
			RenderObject*		renderObject;
			NetworkObject*		networkObject;

			unsigned long layer; // Bit number
			unsigned long layerMask; // Set bit for each layer that this gameobject should not collide with

			bool	isActive;
			string	name;

			std::unordered_map<string, Component*> components;

			Vector3 broadphaseAABB;

		};
	}
}

