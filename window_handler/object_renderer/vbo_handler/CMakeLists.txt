set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(vbo_handler STATIC CGUIVBOHandler.cpp CGUIVBOHandler.hpp)

target_include_directories(vbo_handler PUBLIC ${PROJECT_SOURCE_DIR}/external/glad/include)
target_link_directories(vbo_handler PUBLIC ${PROJECT_SOURCE_DIR}/external/glad/include)
