cmake_minimum_required(VERSION 3.14..3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
	FenkCasterEngine
	VERSION 1.0
	DESCRIPTION "A custom raycaster engine written in c++"
	LANGUAGES CXX)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(app)
add_subdirectory(src)
