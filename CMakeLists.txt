cmake_minimum_required(VERSION 3.14)
## Giving a name to the project
project(weird_golf_game)

#Setup CMake to run tests
enable_testing()

## Including headers, from both the current project and from the imported libraries
include_directories(include)
include_directories(submodules/spdlog)
include_directories(submodules/enet/include)

## I want to use the C++17 standard, forsooth!
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_TESTING ON)

add_subdirectory(submodules/spdlog)
add_subdirectory(submodules/enet)

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
file(GLOB TEST_SRCS /project/UnitTest1/*.cpp)

#Unit Testing
#Run through each source
foreach(testSrc ${TEST_SRCS})
        message(${testSrc})
        #Extract the filename without an extension (NAME_WE)
        get_filename_component(testName ${testSrc} NAME_WE)

        #Add compile target
        add_executable(${testName} ${testSrc})

	#Finally add it to test execution - 
        #Notice the WORKING_DIRECTORY and COMMAND
        add_test(NAME ${testName} 
                 WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/project/UnitTest1/
                 COMMAND ${PROJECT_SOURCE_DIR}/project/UnitTest1/${testName})
endforeach(testSrc)

# OpenGL
find_package(OpenGL REQUIRED)

add_library(lib
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


target_link_libraries(weird_golf_game spdlog::spdlog enet opengl32)

add_executable(test1 ${PROJECT_SOURCE_DIR}/project/UnitTest1/UnitTest1.cpp $<TARGET_OBJECTS:lib>)
target_link_libraries(test1 spdlog::spdlog enet opengl32)
add_test(NAME test1 COMMAND test1.exe)
