set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(vbo_handler STATIC CGUIVBOHandler.cpp CGUIVBOHandler.hpp)

target_include_directories(vbo_handler PUBLIC ../../../external/)
