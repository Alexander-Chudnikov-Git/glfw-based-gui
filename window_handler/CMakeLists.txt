add_subdirectory(debug_handler)
add_subdirectory(object_renderer)
add_subdirectory(shader_compiler)
add_subdirectory(../external/glad/ glad)

find_package(glfw3 3.3 REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(window_handler STATIC CGUIMainWindow.cpp CGUIMainWindow.hpp)

target_include_directories(window_handler PUBLIC debug_handler/ object_renderer/
	shader_compiler/)
target_include_directories(${PROJECT_NAME} PRIVATE ../external/glad)

target_link_directories(window_handler PUBLIC debug_handler/ object_renderer/
	shader_compiler/)
target_link_directories(${PROJECT_NAME} PRIVATE ../external/glad)

target_link_libraries(window_handler debug_handler object_renderer glfw glad
	shader_compiler)

