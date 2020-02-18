cmake_minimum_required(VERSION 3.14)
## Giving a name to the project
project(weird_golf_game)

## Including headers, from both the current project and from the imported libraries
include_directories(include)
include_directories(submodules/spdlog)
include_directories(submodules/enet/include)

## I want to use the C++17 standard, forsooth!
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(submodules/spdlog)
add_subdirectory(submodules/enet)

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

# OpenGL
find_package(OpenGL REQUIRED)

add_executable(weird_golf_game
	${SRC_FILES}
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

##submodules/PhysX/physx/bin/win.x86_64.vc142.mt/debug/glut32.dll submodules/PhysX/physx/bin/win.x86_64.vc142.mt/debug/PhysXDevice64.dll

target_link_libraries(weird_golf_game spdlog::spdlog enet opengl32 PhysX)
