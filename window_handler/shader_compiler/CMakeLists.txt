set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(shader_compiler STATIC CGUIShaderCompiler.cpp CGUIShaderCompiler.hpp)

target_include_directories(shader_compiler PUBLIC ../../external/)
