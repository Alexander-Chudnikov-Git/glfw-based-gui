set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ebo_handler STATIC CGUIEBOHandler.cpp CGUIEBOHandler.hpp)

target_include_directories(ebo_handler PUBLIC ../../../external/)
