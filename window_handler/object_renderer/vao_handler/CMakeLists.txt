set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(vao_handler STATIC CGUIVAOHandler.cpp CGUIVAOHandler.hpp)

include_directories(${PROJECT_SOURCE_DIR}/external/glad/include)
