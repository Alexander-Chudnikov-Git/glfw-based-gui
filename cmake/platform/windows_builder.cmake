set_source_files_properties(${PROJECT_SOURCE_DIR}/resources/resources.rc LANGUAGE RC)

if(MINGW)
    set(CMAKE_RC_COMPILER_INIT windres)
    ENABLE_LANGUAGE(RC)
    SET(CMAKE_RC_COMPILE_OBJECT
    "<CMAKE_RC_COMPILER> <FLAGS> <DEFINES> -o <OBJECT> <SOURCE>")
    set(RC_CFLAGS "-DMINGW -Ocoff")

    # If any sort of debugging is being enabled, add a _DEBUG define to the flags for the resource compiler
    #if(CMAKE_BUILD_TYPE STREQUAL "DEBUG" OR CMAKE_BUILD_TYPE STREQUAL "RELWITHDEBINFO")
    #   set(RC_CFLAGS "${RC_CFLAGS} -D_DEBUG")
    #endif(CMAKE_BUILD_TYPE STREQUAL "DEBUG" OR CMAKE_BUILD_TYPE STREQUAL "RELWITHDEBINFO")
    set_source_files_properties(${PROJECT_SOURCE_DIR}/resources/resources.rc COMPILE_FLAGS "${RC_CFLAGS}")
    set(APP_ICON_RESOURCE_WINDOWS ${PROJECT_SOURCE_DIR}/resources/resources.rc)
else()
    message(FATAL_ERROR "Currently only MINGW supported for windows.")
endif()

add_executable(${PROJECT_NAME} WIN32 main.cpp ${APP_ICON_RESOURCE_WINDOWS}) # Create target build for WIN32 excutable
