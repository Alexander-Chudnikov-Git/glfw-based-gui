set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)												# Set c++ standart to 20

add_library(shader_compiler STATIC CGUIShaderCompiler.cpp CGUIShaderCompiler.hpp)