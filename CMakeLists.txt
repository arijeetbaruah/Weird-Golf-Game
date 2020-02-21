cmake_minimum_required(VERSION 3.14)
## Giving a name to the project
project(weird_golf_game)

SET(CMAKE_EXE_LINKER_FLAGS_CHECKED "")
SET(CMAKE_EXE_LINKER_FLAGS_PROFILE "")

set(PhysX_include_files submodules/PhysX/physx/include)

#Setup CMake to run tests
enable_testing()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

## Including headers, from both the current project and from the imported libraries
include_directories(${PROJECT_SOURCE_DIR}/patches)
include_directories(${PhysX_include_files})
include_directories(${PhysX_include_files}/characterkinematic)
include_directories(${PhysX_include_files}/collision)
include_directories(${PhysX_include_files}/common)
include_directories(${PhysX_include_files}/cooking)
include_directories(${PhysX_include_files}/cudamanager)
include_directories(${PhysX_include_files}/extensions)
include_directories(${PhysX_include_files}/filebuf)
include_directories(${PhysX_include_files}/foundation)
include_directories(${PhysX_include_files}/geometry)
include_directories(${PhysX_include_files}/geomutils)
include_directories(${PhysX_include_files}/gpu)
include_directories(${PhysX_include_files}/pvd)
include_directories(${PhysX_include_files}/solver)
include_directories(${PhysX_include_files}/task)
include_directories(${PhysX_include_files}/vehicle)
include_directories(${PhysX_include_files}/../../pxshared/include)
include_directories(${PhysX_include_files}/../../source)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/submodules/spdlog/include)
include_directories(${PROJECT_SOURCE_DIR}/submodules/enet/include)

## I want to use the C++17 standard, forsooth!
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_TESTING ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/submodules/spdlog)
add_subdirectory(${PROJECT_SOURCE_DIR}/submodules/enet)

option(IsWindows "Is Windows" ON)

# PhysX-specific CMake project setup
set(NV_USE_DEBUG_WINCRT ON CACHE BOOL "Use the debug version of the CRT")
set(PHYSX_ROOT_DIR ${CMAKE_SOURCE_DIR}/submodules/PhysX/physx)
set(PXSHARED_PATH ${PHYSX_ROOT_DIR}/../pxshared)
set(PXSHARED_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CMAKEMODULES_VERSION "1.27")
set(TARGET_BUILD_PLATFORM "windows")
set(CMAKEMODULES_PATH ${PHYSX_ROOT_DIR}/../externals/cmakemodules)
set(PX_OUTPUT_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/externals/physx)
set(PX_OUTPUT_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/externals/physx)

# Call into PhysX's CMake scripts
add_subdirectory(${PHYSX_ROOT_DIR}/compiler/public externals/physx)
#Giacomo's Fix
#add_subdirectory(${PHYSX_ROOT_DIR}/snippets/compiler/cmake/${TARGET_BUILD_PLATFORM})

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB SRC_AI_FILES ${PROJECT_SOURCE_DIR}/src/AI/*.cpp)
file(GLOB HEADER_AI_FILES ${PROJECT_SOURCE_DIR}/include/AI/*.h)
file(GLOB SRC_NETWORK_FILES ${PROJECT_SOURCE_DIR}/src/Network/*.cpp)
file(GLOB HEADER_NETWORK_FILES ${PROJECT_SOURCE_DIR}/include/Network/*.h)
file(GLOB SRC_LOGGER_FILES ${PROJECT_SOURCE_DIR}/src/Logger/*.cpp)
file(GLOB HEADER_LOGGER_FILES ${PROJECT_SOURCE_DIR}/include/Logger/*.h)
file(GLOB SRC_COMMON_FILES ${PROJECT_SOURCE_DIR}/src/Common/*.cpp)
file(GLOB HEADER_COMMON_FILES ${PROJECT_SOURCE_DIR}/include/Common/*.h)
file(GLOB HEADER_COMMON_SUBFILES ${PROJECT_SOURCE_DIR}/include/Common/stb/*.h)
file(GLOB SRC_OPENGLRENDERING_FILES ${PROJECT_SOURCE_DIR}/src/OpenGLRendering/*.cpp ${PROJECT_SOURCE_DIR}/src/OpenGLRendering/*.c)
file(GLOB HEADER_OPENGLRENDERING_FILES ${PROJECT_SOURCE_DIR}/include/OpenGLRendering/*.h)
file(GLOB HEADER_GLAD_FILES ${PROJECT_SOURCE_DIR}/include/glad/*.h)
file(GLOB HEADER_KHR_FILES ${PROJECT_SOURCE_DIR}/include/KHR/*.h)
file(GLOB SRC_ComponentSystem_FILES ${PROJECT_SOURCE_DIR}/src/ComponentSystem/*.cpp)
file(GLOB HEADER_ComponentSystem_FILES ${PROJECT_SOURCE_DIR}/include/ComponentSystem/*.h)
file(GLOB TEST_SRCS ${PROJECT_SOURCE_DIR}/src/UnitTests/*.cpp)
file(GLOB MAIN ${PROJECT_SOURCE_DIR} Main.cpp)
file(GLOB SRC_ComponentSystem_FILES ${PROJECT_SOURCE_DIR}/src/Physics/*.cpp)
file(GLOB HEADER_ComponentSystem_FILES ${PROJECT_SOURCE_DIR}/include/Physics/*.h)

# OpenGL
find_package(OpenGL REQUIRED)

add_library(lib OBJECT
	${SRC_FILES} # removed the main.cpp
	${HEADER_FILES}
	${SRC_LOGGER_FILES}
	${SRC_AI_FILES}
	${SRC_NETWORK_FILES}
	${HEADER_LOGGER_FILES}
	${HEADER_AI_FILES}
	${HEADER_NETWORK_FILES}
	${SRC_COMMON_FILES}
	${HEADER_COMMON_FILES}
	${HEADER_COMMON_SUBFILES}
	${HEADER_OPENGLRENDERING_FILES}
	${SRC_OPENGLRENDERING_FILES}
	${HEADER_GLAD_FILES}
	${HEADER_KHR_FILES}
	${SRC_ComponentSystem_FILES}
	${HEADER_ComponentSystem_FILES}
)

set(CMAKE_EXE_LINKER_FLAGS_CHECKED true)
set(CMAKE_EXE_LINKER_FLAGS_PROFILE true)

if (IsWindows)
	include_directories(${PROJECT_SOURCE_DIR}/submodules/FMOD/windows/api/core/inc)
	include_directories(${PROJECT_SOURCE_DIR}/submodules/FMOD/windows/api/fsbank/inc)
	include_directories(${PROJECT_SOURCE_DIR}/submodules/FMOD/windows/api/studio/inc)

	find_library(
		 fmod_core_windows NAMES fmodL_vc fmod_vc HINTS "${PROJECT_SOURCE_DIR}/submodules/FMOD/windows/api/core/lib/x64"
	)

	find_library(
		fmod_fsbank_windows NAMES fsbank_vc HINTS "${PROJECT_SOURCE_DIR}/submodules/FMOD/windows/api/fsbank/lib/x64"
	)

	find_library(
		fmod_studio_windows NAMES fmodstudio_vc fmodstudioL_vc HINTS "${PROJECT_SOURCE_DIR}/submodules/FMOD/windows/api/studio/lib/x64"
	)

	add_executable(weird_golf_game
		#added the main
		${MAIN}
	)

	target_link_libraries(weird_golf_game lib spdlog::spdlog enet opengl32 PhysX
		${fmod_core_windows}
		${fmod_fsbank_windows}
		${fmod_studio_windows}
	)

else()

	include_directories(${PROJECT_SOURCE_DIR}/submodules/FMOD/PS4/api/core/inc)
	include_directories(${PROJECT_SOURCE_DIR}/submodules/FMOD/PS4/api/fsbank/inc)
	include_directories(${PROJECT_SOURCE_DIR}/submodules/FMOD/PS4/api/studio/inc)

	set (fmod_core_PS4
		${PROJECT_SOURCE_DIR}/submodules/FMOD/PS4/api/core/lib/libfmod_stub_weak.a
		${PROJECT_SOURCE_DIR}/submodules/FMOD/PS4/api/core/lib/libfmodL_stub_weak.a
	)

	set (fmod_studio_PS4
		${PROJECT_SOURCE_DIR}/submodules/FMOD/PS4/api/studio/lib/libfmodstudio_stub_weak.a
		${PROJECT_SOURCE_DIR}/submodules/FMOD/PS4/api/studio/lib/libfmodstudioL_stub_weak.a
	)

	add_executable(weird_golf_game
		#added the main
		${MAIN}
	)

	target_link_libraries(weird_golf_game lib spdlog::spdlog enet opengl32 PhysX
		${fmod_core_PS4}
		${fmod_studio_PS4}
	)

endif()

add_executable(test1 ${PROJECT_SOURCE_DIR}/src/UnitTests/UnitTest1.cpp $<TARGET_OBJECTS:lib>)
target_link_libraries(test1 spdlog::spdlog enet opengl32)
add_test(NAME test1 COMMAND test1.exe)

add_executable(test2 ${PROJECT_SOURCE_DIR}/src/UnitTests/UnitTest2.cpp $<TARGET_OBJECTS:lib>)
target_link_libraries(test2 spdlog::spdlog enet opengl32)
add_test(NAME test2 COMMAND test2.exe)

add_executable(ComponentTest ${PROJECT_SOURCE_DIR}/src/UnitTests/ComponentTest.cpp $<TARGET_OBJECTS:lib>)
target_link_libraries(ComponentTest spdlog::spdlog enet opengl32)
add_Test(NAME ComponentTest COMMAND ComponentTest.exe)

add_executable(AITest ${PROJECT_SOURCE_DIR}/src/UnitTests/AITest.cpp $<TARGET_OBJECTS:lib>)
target_link_libraries(AITest spdlog::spdlog enet opengl32)
add_Test(NAME AITest COMMAND AITest.exe)
##submodules/PhysX/physx/bin/win.x86.vc142.mt/debug/glut32.dll submodules/PhysX/physx/bin/win.x86.vc142.mt/debug/PhysXDevice64.dll


target_link_libraries(weird_golf_game lib spdlog::spdlog enet opengl32 
	${PROJECT_SOURCE_DIR}/submodules/physx_req/lib/LowLevel_static_64.lib
	${PROJECT_SOURCE_DIR}/submodules/physx_req/lib/LowLevelAABB_static_64.lib
	${PROJECT_SOURCE_DIR}/submodules/physx_req/lib/LowLevelDynamics_static_64.lib
	${PROJECT_SOURCE_DIR}/submodules/physx_req/lib/PhysX_64.lib
	${PROJECT_SOURCE_DIR}/submodules/physx_req/lib/PhysXCharacterKinematic_static_64.lib
	${PROJECT_SOURCE_DIR}/submodules/physx_req/lib/PhysXCommon_64.lib
	${PROJECT_SOURCE_DIR}/submodules/physx_req/lib/PhysXCooking_64.lib
	${PROJECT_SOURCE_DIR}/submodules/physx_req/lib/PhysXExtensions_static_64.lib
	${PROJECT_SOURCE_DIR}/submodules/physx_req/lib/PhysXFoundation_64.lib
	${PROJECT_SOURCE_DIR}/submodules/physx_req/lib/PhysXPvdSDK_static_64.lib
	${PROJECT_SOURCE_DIR}/submodules/physx_req/lib/PhysXTask_static_64.lib
	${PROJECT_SOURCE_DIR}/submodules/physx_req/lib/PhysXVehicle_static_64.lib
	${PROJECT_SOURCE_DIR}/submodules/physx_req/lib/SceneQuery_static_64.lib)

