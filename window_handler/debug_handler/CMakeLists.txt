set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)												# Set c++ standart to 20

add_library(debug_handler STATIC CGUIDebugHandler.cpp CGUIDebugHandler.hpp)