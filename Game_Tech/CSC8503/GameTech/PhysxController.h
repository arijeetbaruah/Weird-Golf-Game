// @Author: Christopher Cometto
#pragma once

#include "PxPhysicsAPI.h"
#include <vector>
#define PVD_HOST "127.0.0.1"

using namespace physx;

// Singleton
class PhysxController {
private:
	static PhysxController* instance;
	PhysxController();

	PxDefaultAllocator		gAllocator;
	PxDefaultErrorCallback	gErrorCallback;

	PxFoundation* gFoundation = NULL;
	PxPhysics* gPhysics = NULL;
	PxDefaultCpuDispatcher* gDispatcher = NULL;

	PxCooking* gCooking = NULL;

	PxPvd* gPvd = NULL;

	PxScene* actualScene = NULL;
public:
	static PhysxController& getInstance() {
		static PhysxController instance;
		return instance;
	}

	void stepPhysics(bool interactive, float dt);
	void createDefaultScene();
	void addTriangleMeshToScene(std::vector<PxVec3> verts, std::vector<PxU32> tris);
	void spawnBall();
};

