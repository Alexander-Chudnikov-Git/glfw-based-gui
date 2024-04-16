set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(vao_handler STATIC CGUIVAOHandler.cpp CGUIVAOHandler.hpp)

target_include_directories(vao_handler PUBLIC ../../../external/)
