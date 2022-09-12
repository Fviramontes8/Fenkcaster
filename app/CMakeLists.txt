cmake_minimum_required(VERSION 3.14..3.20)

add_executable(
	${PROJECT_NAME} 
	../src/draw_shapes.cpp 
	../src/player_utils.cpp 
	app.cpp
)
target_link_libraries(${PROJECT_NAME} OpenGL::GL GLUT::GLUT OpenGL::GLU)
