set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(vbo_handler STATIC CGUIVBOHandler.cpp CGUIVBOHandler.hpp)

include_directories(${PROJECT_SOURCE_DIR}/external/glad/include)
