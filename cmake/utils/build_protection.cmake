message(STATUS "Source directory:  ${CMAKE_SOURCE_DIR}")
message(STATUS "Build directory:   ${CMAKE_BINARY_DIR}")

# Make sure we are not building in top level directory
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-tree build are not allowed.")
endif()
