// @Author: Christopher Cometto

#include "PhysxController.h"


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

PxFilterFlags contactReportFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
										PxFilterObjectAttributes attributes1, PxFilterData filterData1,
										PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize) {
	// let triggers through
	if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1)) {
		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
		return PxFilterFlag::eDEFAULT;
	}
	// generate contacts for all that were not filtered above
	pairFlags = PxPairFlag::eCONTACT_DEFAULT;

	// trigger the contact callback for pairs (A,B) where
	// the filtermask of A contains the ID of B and vice versa.
	if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;

	return PxFilterFlag::eDEFAULT;
}

void PhysxController::createDefaultScene() {
	sceneDesc = new PxSceneDesc(gPhysics->getTolerancesScale());
	sceneDesc->gravity = PxVec3(0.0f, -9.81f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc->cpuDispatcher = gDispatcher;
	sceneDesc->filterShader = contactReportFilterShader;
	sceneDesc->simulationEventCallback = &testCallback;
	//sceneDesc->contactModifyCallback = &testCallback;
	actualScene = gPhysics->createScene(*sceneDesc);

	gCooking = PxCreateCooking(PX_PHYSICS_VERSION, *gFoundation, PxCookingParams(gPhysics->getTolerancesScale()));

	PxPvdSceneClient* pvdClient = actualScene->getScenePvdClient();
	if (pvdClient) {
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}
}

void PhysxController::addActor(PxActor* actor) {
	actualScene->addActor(*actor);
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
