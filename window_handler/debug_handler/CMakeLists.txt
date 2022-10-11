add_subdirectory(../protection protection)													# Add protection subdirectory in order to load library

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)												# Set c++ standart to 20

add_library(debug_handler STATIC CGUIDebugHandler.cpp CGUIDebugHandler.hpp)

target_include_directories(debug_handler PUBLIC ../protection/)	
target_link_directories(debug_handler PUBLIC ../protection/)
target_link_libraries(debug_handler protection)