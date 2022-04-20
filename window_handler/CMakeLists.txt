add_subdirectory(glad)															# Add glad subdirectory in order to load library
add_subdirectory(glm)															# Add glm subdirectory in order to load library
add_subdirectory(GLFW)															# Add GLFW subdirectory in order to load library
add_subdirectory(debug_handler)													# Add debug_handler subdirectory in order to load library
add_subdirectory(vertex_specification/vbo_handler)								# Add vbo_handler subdirectory in order to load library
add_subdirectory(vertex_specification/vao_handler)								# Add vao_handler subdirectory in order to load library
add_subdirectory(vertex_specification/ebo_handler)								# Add ebo_handler subdirectory in order to load library
add_subdirectory(cgui_datatypes)												# Add cgui_datatypes subdirectory in order to load library
add_subdirectory(shader_compiler)												# Add shader_compiler subdirectory in order to load library

find_package(glfw3 3.3 REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)												# Set c++ standart to 20

add_library(window_handler STATIC CGUIMainWindow.cpp CGUIMainWindow.hpp)		# Create library that later would be linked to main project

target_include_directories(window_handler PUBLIC glad/ glfw/ glm/ 
	debug_handler/ vertex_specification/vbo_handler/ 
	vertex_specification/vao_handler/ cgui_datatypes/ 
	vertex_specification/ebo_handler/ shader_compiler/)							# Link include directories
target_link_directories(window_handler PUBLIC glad/ glfw/ glm/ 
	debug_handler/ vertex_specification/vbo_handler/ 
	vertex_specification/vao_handler/ cgui_datatypes/ 
	vertex_specification/ebo_handler/ shader_compiler/)							# Link directories for libraries

target_link_libraries(window_handler debug_handler vbo_handler vao_handler 
	ebo_handler cgui_datatypes glad glfw glm shader_compiler)