// @Author: Christopher Cometto

#include "PhysxController.h"

PhysxController::PhysxController() {
	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	createDefaultScene(); createDefaultScene(); createDefaultScene();

}

void PhysxController::stepPhysics(bool interactive, float dt) {
	actualScene->simulate(dt);
	actualScene->fetchResults(interactive);
}

PxFilterFlags contactReportFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
										PxFilterObjectAttributes attributes1, PxFilterData filterData1,
										PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize) {
	// all initial and persisting reports for everything, with per-point data
	PX_UNUSED(attributes0);
	PX_UNUSED(attributes1);
	PX_UNUSED(filterData0);
	PX_UNUSED(filterData1);
	PX_UNUSED(constantBlockSize);
	PX_UNUSED(constantBlock);
	pairFlags = PxPairFlag::eSOLVE_CONTACT 
		| PxPairFlag::eDETECT_DISCRETE_CONTACT
		| PxPairFlag::eNOTIFY_TOUCH_FOUND
		| PxPairFlag::eNOTIFY_TOUCH_PERSISTS
		| PxPairFlag::eNOTIFY_CONTACT_POINTS;
	return PxFilterFlag::eDEFAULT;
}

void PhysxController::createDefaultScene() {
	sceneDesc = new PxSceneDesc(gPhysics->getTolerancesScale());
	sceneDesc->gravity = PxVec3(0.0f, -9.81f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc->cpuDispatcher = gDispatcher;
	sceneDesc->filterShader = contactReportFilterShader;
	sceneDesc->simulationEventCallback = &callback;
	//sceneDesc->contactModifyCallback = &testCallback;
	actualScene = gPhysics->createScene(*sceneDesc);
	addScene(actualScene);
	gCooking = PxCreateCooking(PX_PHYSICS_VERSION, *gFoundation, PxCookingParams(gPhysics->getTolerancesScale()));
}

void PhysxController::addActor(PxActor* actor, int index) {
	scenes[index]->addActor(*actor);
}

void PhysxController::removeActor(PxActor* actor) {
	actualScene->removeActor(*actor);
}

void PhysxController::addScene(PxScene* scene) {
	scenes.push_back(scene);
	PxPvdSceneClient* pvdClient = scene->getScenePvdClient();
	if (pvdClient) {
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
}

void PhysxController::setActiveScene(int index) {
	actualScene = scenes[index];
}

void PhysxController::setupFiltering(PxRigidActor* actor, PxU32 filterGroup, PxU32 filterMask) {
	PxFilterData filterData;
    filterData.word0 = filterGroup; // word0 = own ID
    filterData.word1 = filterMask;  // word1 = ID mask to filter pairs that trigger a
                                    // contact callback;
    const PxU32 numShapes = actor->getNbShapes();
    PxShape** shapes = (PxShape**)malloc(sizeof(PxShape*)*numShapes);
    actor->getShapes(shapes, numShapes);
    for(PxU32 i = 0; i < numShapes; i++)
    {
        PxShape* shape = shapes[i];
        shape->setSimulationFilterData(filterData);
    }
    free(shapes);
}
