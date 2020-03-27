#pragma once
#include <vector>
#include "Ray.h"
#include "CollisionDetection.h"
#include "QuadTree.h"
namespace NCL {
		class Camera;
		using Maths::Ray;
	namespace CSC8503 {
		class GameObject;
		class Constraint;

		typedef std::function<void(GameObject*)> GameObjectFunc;
		typedef std::vector<GameObject*>::const_iterator GameObjectIterator;

		class GameWorld	{
		public:
			GameWorld();
			~GameWorld();

			void Clear();
			void ClearAndErase();

			void AddGameObject(GameObject* o);
			void RemoveGameObject(GameObject* o);

			void AddConstraint(Constraint* c);
			void RemoveConstraint(Constraint* c);

			void AddCollectable(GameObject* c);
			void RemoveCollectable(GameObject* c);

			Camera* GetMainCamera() const {
				return mainCamera;
			}

			void ShuffleConstraints(bool state) {
				shuffleConstraints = state;
			}

			void ShuffleObjects(bool state) {
				shuffleObjects = state;
			}

			vector<GameObject*> starList;

			bool Raycast(Ray& r, RayCollision& closestCollision, bool closestObject = false) const;

			virtual void UpdateWorld(float dt);

			void OperateOnContents(GameObjectFunc f);

			void GetObjectIterators(
				GameObjectIterator& first,
				GameObjectIterator& last) const;

			void GetConstraintIterators(
				std::vector<Constraint*>::const_iterator& first,
				std::vector<Constraint*>::const_iterator& last) const;

			void SetIsServer(bool b) { isServer = b; };
			void SetIsNetworkedGame(bool b) { isNetworkedGame = b; };

			bool GetIsServer() { return isServer; };
			bool GetIsNetworkedGame() { return isNetworkedGame; };

			void SetUIactive(bool state) { isUIactive = state; }
			bool GetUIactive() { return isUIactive; }

			void SetPlayer(GameObject* p) { player = p; };
			GameObject* GetPlayer() { return player; };

			void SetServerPlayer(GameObject* p, int index) { serverPlayers.insert(std::pair<int, GameObject*>(index, p)); };
			GameObject* GetServerPlayer(int index) { return serverPlayers.at(index); };

			void SetObjectList(std::vector<GameObject*> newList) { gameObjects = newList; }
		protected:
			void UpdateTransforms();
			void UpdateQuadTree();

			std::vector<GameObject*> gameObjects;

			std::vector<Constraint*> constraints;

			int CollectableCount;

			QuadTree<GameObject*>* quadTree;

			std::map<int, GameObject*> serverPlayers;

			Camera* mainCamera;

			GameObject* player;

			bool isServer;
			bool isNetworkedGame;

			bool shuffleConstraints;
			bool shuffleObjects;
			bool isUIactive;
		};
	}
}

