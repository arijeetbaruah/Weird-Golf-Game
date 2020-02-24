// @Author: Christopher Cometto

#include "PhysxController.h"

#include "PhysxController.h"
#include "PxPhysicsAPI.h"

PhysxController::PhysxController() {
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	createDefaultScene();
}

void PhysxController::stepPhysics(bool interactive, float dt) {
	actualScene->simulate(dt);
	actualScene->fetchResults(interactive);
}

void PhysxController::createDefaultScene() {
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	actualScene = gPhysics->createScene(sceneDesc);

	gCooking = PxCreateCooking(PX_PHYSICS_VERSION, *gFoundation, PxCookingParams(gPhysics->getTolerancesScale()));

	PxPvdSceneClient* pvdClient = actualScene->getScenePvdClient();
	if (pvdClient) {
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0, 1, 0, 0), *gPhysics->createMaterial(0.5f, 0.5f, 0.6f));
	actualScene->addActor(*groundPlane);
}

void PhysxController::addTriangleMeshToScene(std::vector<PxVec3> verts, std::vector<PxU32> tris) {
	PxTriangleMeshDesc meshDesc;

	meshDesc.points.count = verts.size();
	meshDesc.points.stride = sizeof(PxVec3);
	meshDesc.points.data = &verts[0];

	meshDesc.triangles.count = tris.size() / 3;
	meshDesc.triangles.stride = 3 * sizeof(PxU32);
	meshDesc.triangles.data = &tris[0];

	PxDefaultMemoryOutputStream writeBuffer;
	PxTriangleMeshCookingResult::Enum result;
	bool status = gCooking->cookTriangleMesh(meshDesc, writeBuffer, &result);

	PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
	PxTriangleMesh* mesh = gPhysics->createTriangleMesh(readBuffer);
	PxTriangleMeshGeometry geom(mesh);

	PxTransform t = PxTransform(PxVec3(0, 0, 0));
	PxTransform localTm(PxVec3(0, 0, 0));
	PxRigidDynamic* meshActor = gPhysics->createRigidDynamic(t.transform(localTm));
	PxShape* meshShape;
	if (meshActor) {
		meshActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
		meshShape = PxRigidActorExt::createExclusiveShape(*meshActor, geom, *gPhysics->createMaterial(0.5f, 0.5f, 0.6f));
		actualScene->addActor(*meshActor);
	}
}

void PhysxController::spawnBall() {
	PxShape* shape = gPhysics->createShape(PxSphereGeometry(3.0), *gPhysics->createMaterial(0.5f, 0.5f, 0.6f));
	PxTransform localTm(PxVec3(0, 0, 0));
	PxTransform t();
	PxRigidDynamic* body = gPhysics->createRigidDynamic(PxTransform(localTm));
	body->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
	actualScene->addActor(*body);
}
