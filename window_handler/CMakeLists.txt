include(FetchContent)

add_subdirectory(debug_handler)
add_subdirectory(object_renderer)
add_subdirectory(shader_compiler)

# find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Specify glad settings
#glad_add_library(glad_gl_core_46 STATIC REPRODUCIBLE LOCATION
#                                 ${PROJECT_SOURCE_DIR}/external/glad/
#                                 API gl:core=4.6)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    CONFIGURE_COMMAND "-D GLFW_BUILD_X11=1"
    BUILD_COMMAND ""
)
FetchContent_MakeAvailable(glfw)

add_library(window_handler STATIC CGUIMainWindow.cpp CGUIMainWindow.hpp)

add_library(glad STATIC ${PROJECT_SOURCE_DIR}/external/glad/src/glad.c
                        ${PROJECT_SOURCE_DIR}/external/glad/include/glad/glad.h)

target_include_directories(glad PRIVATE ${PROJECT_SOURCE_DIR}/external/glad/include/)
target_link_directories(glad PRIVATE ${PROJECT_SOURCE_DIR}/external/glad/include/)

target_include_directories(window_handler PUBLIC ${GLFW_SOURCE_DIR}
    debug_handler/ shader_compiler/ object_renderer/ ${PROJECT_SOURCE_DIR}/external/glad/include/)

target_link_directories(window_handler PUBLIC ${GLFW_BINARY_DIR} debug_handler/
    shader_compiler/ object_renderer/ ${PROJECT_SOURCE_DIR}/external/glad/include/)

target_link_libraries(window_handler PUBLIC asan glad glfw debug_handler
    object_renderer shader_compiler OpenGL::GL)
