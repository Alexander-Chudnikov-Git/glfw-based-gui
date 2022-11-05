add_subdirectory(glm)					# Add glm subdirectory in order to load library
add_subdirectory(vbo_handler)			# Add vbo_handler subdirectory in order to load library
add_subdirectory(vao_handler)			# Add vao_handler subdirectory in order to load library
add_subdirectory(ebo_handler)			# Add ebo_handler subdirectory in order to load library

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)												# Set c++ standart to 20

add_library(object_renderer STATIC CGUIObjectRenderer.cpp CGUIObjectRenderer.hpp)		# Create library that later would be linked to main project

target_include_directories(object_renderer PUBLIC glm/ 
	vbo_handler/ vao_handler/ ebo_handler/)							# Link include directories

target_link_directories(object_renderer PUBLIC glm/ 
	vbo_handler/ vao_handler/ ebo_handler/)							# Link directories for libraries

target_link_libraries(object_renderer vbo_handler vao_handler 
	ebo_handler glm)