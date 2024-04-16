add_subdirectory(vbo_handler)
add_subdirectory(vao_handler)
add_subdirectory(ebo_handler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(object_renderer STATIC CGUIObjectRenderer.cpp CGUIObjectRenderer.hpp)

target_include_directories(object_renderer PUBLIC vbo_handler/ vao_handler/
	ebo_handler/)

target_link_directories(object_renderer PUBLIC vbo_handler/ vao_handler/
	ebo_handler/)

target_link_libraries(object_renderer vbo_handler vao_handler ebo_handler glm)
