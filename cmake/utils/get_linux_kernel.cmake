execute_process(
    COMMAND cat /etc/os-release
    COMMAND grep -oP "^ID=\\K[a-zA-Z0-9]*"
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    RESULT_VARIABLE OS_RELEASE_RESULT
    OUTPUT_VARIABLE CMAKE_SYSTEM_ID
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(OS_RELEASE_RESULT)
    message(WARNING "Unknown kernel ID, /etc/os-release not found.")
    set(CMAKE_SYSTEM_ID "unknown")
endif()

# Print each variable for verification
message(STATUS "Kernel Name:       ${CMAKE_SYSTEM_NAME}")
message(STATUS "Kernel Version:    ${CMAKE_SYSTEM_VERSION}")
message(STATUS "Kernel ID:         ${CMAKE_SYSTEM_ID}")
message(STATUS "Processor:         ${CMAKE_SYSTEM_PROCESSOR}")

if("${CMAKE_SYSTEM_ID}" STREQUAL "arch")
    include(cmake/utils/arch_furry_animation.cmake)
elseif("${CMAKE_SYSTEM_ID}" STREQUAL "ubuntu")
    message(WARNING "I highly doubdt that you know what you are doing :/")
endif()
