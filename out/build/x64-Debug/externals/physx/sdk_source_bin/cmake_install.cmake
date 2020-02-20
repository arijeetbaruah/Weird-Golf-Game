# Install script for directory: C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/PhysX/source/compiler/cmake

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/source/foundation/include/windows" TYPE FILE FILES
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/windows/PsWindowsAoS.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/windows/PsWindowsFPU.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/windows/PsWindowsInclude.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/windows/PsWindowsInlineAoS.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/windows/PsWindowsIntrinsics.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/windows/PsWindowsTrigConstants.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/windows/PxWindowsIntrinsics.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/windows" TYPE FILE FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/windows/PxWindowsIntrinsics.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/unix/PxUnixIntrinsics.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/unix" TYPE FILE FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/unix/PxUnixIntrinsics.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE FILE OPTIONAL FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysXFoundation.pdb")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxFoundation.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/foundation" TYPE FILE FILES
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/foundation/PxAssert.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/foundation/PxFoundationConfig.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/foundation/PxMathUtils.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/source/foundation/include" TYPE FILE FILES
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/Ps.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsAlignedMalloc.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsAlloca.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsAllocator.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsAoS.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsArray.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsAtomic.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsBasicTemplates.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsBitUtils.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsBroadcast.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsCpu.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsFoundation.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsFPU.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsHash.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsHashInternals.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsHashMap.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsHashSet.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsInlineAllocator.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsInlineAoS.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsInlineArray.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsIntrinsics.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsMathUtils.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsMutex.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsPool.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsSList.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsSocket.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsSort.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsSortInternals.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsString.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsSync.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsTempAllocator.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsThread.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsTime.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsUserAllocated.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsUtilities.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsVecMath.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsVecMathAoSScalar.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsVecMathAoSScalarInline.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsVecMathSSE.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsVecMathUtilities.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsVecQuat.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/foundation/include/PsVecTransform.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/Px.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxAllocatorCallback.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxProfiler.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxSharedAssert.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxBitAndData.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxBounds3.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxErrorCallback.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxErrors.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxFlags.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxIntrinsics.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxIO.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxMat33.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxMat44.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxMath.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxMemory.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxPlane.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxPreprocessor.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxQuat.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxSimpleTypes.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxStrideIterator.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxTransform.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxUnionCast.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxVec2.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxVec3.h;C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation/PxVec4.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "C:/Users/b6024306/source/Group Work/weird-golf-game/out/install/x64-Debug/include/foundation" TYPE FILE FILES
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/Px.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxAllocatorCallback.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxProfiler.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxSharedAssert.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxBitAndData.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxBounds3.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxErrorCallback.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxErrors.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxFlags.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxIntrinsics.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxIO.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxMat33.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxMat44.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxMath.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxMemory.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxPlane.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxPreprocessor.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxQuat.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxSimpleTypes.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxStrideIterator.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxTransform.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxUnionCast.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxVec2.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxVec3.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/../pxshared/include/foundation/PxVec4.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gpu" TYPE FILE FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/gpu/PxGpu.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cudamanager" TYPE FILE FILES
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/cudamanager/PxCudaContextManager.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/cudamanager/PxCudaMemoryManager.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/common/windows" TYPE FILE FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/common/windows/PxWindowsDelayLoadHook.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE FILE OPTIONAL FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysX.pdb")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxActor.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxAggregate.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxArticulationReducedCoordinate.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxArticulationBase.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxArticulation.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxArticulationJoint.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxArticulationJointReducedCoordinate.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxArticulationLink.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxBatchQuery.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxBatchQueryDesc.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxBroadPhase.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxClient.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxConstraint.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxConstraintDesc.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxContact.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxContactModifyCallback.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxDeletionListener.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxFiltering.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxForceMode.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxImmediateMode.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxLockedData.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxMaterial.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxPhysics.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxPhysicsAPI.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxPhysicsSerialization.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxPhysicsVersion.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxPhysXConfig.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxPruningStructure.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxQueryFiltering.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxQueryReport.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxRigidActor.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxRigidBody.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxRigidDynamic.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxRigidStatic.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxScene.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxSceneDesc.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxSceneLock.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxShape.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxSimulationEventCallback.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxSimulationStatistics.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxVisualizationParameter.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/common" TYPE FILE FILES
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/common/PxBase.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/common/PxCollection.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/common/PxCoreUtilityTypes.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/common/PxMetaData.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/common/PxMetaDataFlags.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/common/PxPhysicsInsertionCallback.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/common/PxPhysXCommonConfig.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/common/PxRenderBuffer.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/common/PxSerialFramework.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/common/PxSerializer.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/common/PxStringTable.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/common/PxTolerancesScale.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/common/PxTypeInfo.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/common/PxProfileZone.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/pvd" TYPE FILE FILES
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/pvd/PxPvdSceneClient.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/pvd/PxPvd.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/pvd/PxPvdTransport.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/collision" TYPE FILE FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/collision/PxCollisionDefs.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/solver" TYPE FILE FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/solver/PxSolverDefs.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/PxConfig.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE FILE OPTIONAL FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/bin/win.x86_64.vc142.md/debug/PhysXCharacterKinematic_static.pdb")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/characterkinematic" TYPE FILE FILES
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/characterkinematic/PxBoxController.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/characterkinematic/PxCapsuleController.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/characterkinematic/PxController.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/characterkinematic/PxControllerBehavior.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/characterkinematic/PxControllerManager.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/characterkinematic/PxControllerObstacles.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/characterkinematic/PxExtended.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE FILE OPTIONAL FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysXCommon.pdb")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/geometry" TYPE FILE FILES
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxBoxGeometry.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxCapsuleGeometry.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxConvexMesh.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxConvexMeshGeometry.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxGeometry.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxGeometryHelpers.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxGeometryQuery.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxHeightField.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxHeightFieldDesc.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxHeightFieldFlag.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxHeightFieldGeometry.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxHeightFieldSample.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxMeshQuery.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxMeshScale.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxPlaneGeometry.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxSimpleTriangleMesh.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxSphereGeometry.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxTriangle.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxTriangleMesh.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxTriangleMeshGeometry.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geometry/PxBVHStructure.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/geomutils" TYPE FILE FILES
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geomutils/GuContactBuffer.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/geomutils/GuContactPoint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE FILE OPTIONAL FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysXCooking.pdb")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cooking" TYPE FILE FILES
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/cooking/PxBVH33MidphaseDesc.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/cooking/PxBVH34MidphaseDesc.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/cooking/Pxc.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/cooking/PxConvexMeshDesc.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/cooking/PxCooking.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/cooking/PxMidphaseDesc.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/cooking/PxTriangleMeshDesc.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/cooking/PxBVHStructureDesc.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE FILE OPTIONAL FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/bin/win.x86_64.vc142.md/debug/PhysXExtensions_static.pdb")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/extensions" TYPE FILE FILES
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxBinaryConverter.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxBroadPhaseExt.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxCollectionExt.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxConstraintExt.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxContactJoint.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxConvexMeshExt.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxD6Joint.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxD6JointCreate.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxDefaultAllocator.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxDefaultCpuDispatcher.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxDefaultErrorCallback.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxDefaultSimulationFilterShader.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxDefaultStreams.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxDistanceJoint.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxContactJoint.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxExtensionsAPI.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxFixedJoint.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxJoint.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxJointLimit.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxMassProperties.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxPrismaticJoint.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxRaycastCCD.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxRepXSerializer.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxRepXSimpleType.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxRevoluteJoint.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxRigidActorExt.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxRigidBodyExt.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxSceneQueryExt.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxSerialization.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxShapeExt.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxSimpleFactory.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxSmoothNormals.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxSphericalJoint.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxStringTableExt.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/extensions/PxTriangleMeshExt.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/filebuf" TYPE FILE FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/filebuf/PxFileBuf.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE FILE OPTIONAL FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/bin/win.x86_64.vc142.md/debug/PhysXVehicle_static.pdb")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vehicle" TYPE FILE FILES
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/vehicle/PxVehicleComponents.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/vehicle/PxVehicleDrive.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/vehicle/PxVehicleDrive4W.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/vehicle/PxVehicleDriveNW.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/vehicle/PxVehicleDriveTank.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/vehicle/PxVehicleNoDrive.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/vehicle/PxVehicleSDK.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/vehicle/PxVehicleShaders.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/vehicle/PxVehicleTireFriction.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/vehicle/PxVehicleUpdate.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/vehicle/PxVehicleUtil.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/vehicle/PxVehicleUtilControl.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/vehicle/PxVehicleUtilSetup.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/vehicle/PxVehicleUtilTelemetry.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/vehicle/PxVehicleWheels.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/source/fastxml/include" TYPE FILE FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/source/fastxml/include/PsFastXml.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE FILE OPTIONAL FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/bin/win.x86_64.vc142.md/debug/PhysXPvdSDK_static.pdb")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE FILE OPTIONAL FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/bin/win.x86_64.vc142.md/debug/PhysXTask_static.pdb")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/task" TYPE FILE FILES
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/task/PxCpuDispatcher.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/task/PxTask.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/task/PxTaskDefine.h"
    "C:/Users/b6024306/source/Group Work/weird-golf-game/submodules/PhysX/physx/include/task/PxTaskManager.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysXFoundation.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE SHARED_LIBRARY FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysXFoundation.dll")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysX.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE SHARED_LIBRARY FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysX.dll")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE STATIC_LIBRARY FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysXCharacterKinematic_static.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE STATIC_LIBRARY FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysXPvdSDK_static.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysXCommon.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE SHARED_LIBRARY FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysXCommon.dll")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysXCooking.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE SHARED_LIBRARY FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysXCooking.dll")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE STATIC_LIBRARY FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysXExtensions_static.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE STATIC_LIBRARY FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysXVehicle_static.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/win.x86_64.vc142.md/debug" TYPE STATIC_LIBRARY FILES "C:/Users/b6024306/source/Group Work/weird-golf-game/out/build/x64-Debug/externals/physx/bin/win.x86_64.vc142.md/debug/PhysXTask_static.lib")
endif()

