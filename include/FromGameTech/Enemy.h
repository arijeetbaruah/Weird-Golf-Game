#pragma once
#include "ComponentSystem\GameObject.h"
#include "FromGameTech\GameWorld.h"
#include "Common/Window.h"
#include "Common/Camera.h"
#include "AI/StateMachine.h"
#include "AI//StateTransition.h"
#include "AI//State.h"
#include "EnemyPatrolSuperState.h"
#include "EnemyChaseSuperState.h"
#include <cmath>
#include "Player.h"
#define PI 3.14159265

		class Enemy : public GameObject
		{
		public:
			Enemy(Vector3 position, GameWorld* world, bool& isServer);
			~Enemy();
			virtual void Update(float dt);
			virtual void Trigger(GameObject& obj);

			void Patrol(float dt);
			void Idle(float dt);
			void Chase(float dt);
			void Attack(float dt);

			void setTimeSpentIdle(float t) { timeSpentIdle = t; };
			float& getTimeSpentIdle() { return timeSpentIdle; };

			void setTimeSpentPatrolling(float t) { timeSpentPatrolling = t; };
			float& getTimeSpentPatrolling() { return timeSpentPatrolling; };

			float getTimeToSpendIdle() { return timeToSpendIdle; };
			float getTimeToSpendPatrolling() { return timeToSpendPatrolling; };

			float& getDistanceFromPlayer() { return distanceFromPlayer; };
			float getChaseRadius() { return chaseRadius; };
			float getAttackRadius() { return attackRadius; };

			void setPlayer(GameObject* p) { player = p; };
			void setPlayerTwo(GameObject* p) { playerTwo = p; };

			void RotateTowards(Vector3 v);

			void resetPosition();

		protected:
			void GeneratePath();
			int roundToNearestTen(int num);
			void DisplayPathfinding();

			void InitStateMachine();

			GameWorld* gameWorld;

			float speed; 
			float chaseSpeed;
			float rotationSpeed;

			StateMachine* testMachine;

			float timeSpentIdle;
			float timeSpentPatrolling;

			float timeToSpendIdle;
			float timeToSpendPatrolling;

			float distanceFromPlayer;
			float chaseRadius;
			float attackRadius;

			float attackTimer;
			float attackCooldown;

			bool& isServerEnemy;

			GameObject* player;
			GameObject* playerTwo;
			GameObject* closestPlayer;

			StateMachine* stateMachine;

			std::vector<Vector3> pathNodes;
			int index;
			Vector3 pathfindingOffSet;
			Vector3 currentDirection;
		};
