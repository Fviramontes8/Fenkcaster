set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/fenkcaster/draw_shapes.hpp")

add_library(fenkcaster_lib draw_shapes.cpp ${HEADER_LIST})

target_include_directories(fenkcaster_lib PUBLIC ../include)

target_compile_features(fenkcaster_lib PUBLIC cxx_std_20)

source_group(
	TREE "${PROJECT_SOURCE_DIR}/include"
	PREFIX "Header Files"
	FILES ${HEADER_LIST})
