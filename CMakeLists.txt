cmake_minimum_required(VERSION 3.21.1)									# Minimum required CMake version

set(PROJECT_NAME "glfw-based-gui")
project(${PROJECT_NAME})												# Set name to the project

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)										# Set c++ standard to 20
set(CMAKE_RELEASE ON)
set(CMAKE_UPX_COMPRESS ON)

if (APPLE)
	set(ICON_NAME "icon.icns")
	set(ICON_PATH ${PROJECT_SOURCE_DIR}/resources/${ICON_NAME})

	set(VS_SHADER_NAME "cgui_tri_vert.vs")
	set(VS_SHADER_PATH ${PROJECT_SOURCE_DIR}/resources/${VS_SHADER_NAME})

	set(FS_SHADER_NAME "cgui_tri_frag.fs")
	set(FS_SHADER_PATH ${PROJECT_SOURCE_DIR}/resources/${FS_SHADER_NAME})

	set(GS_SHADER_NAME "cgui_tri_geom.gs")
	set(GS_SHADER_PATH ${PROJECT_SOURCE_DIR}/resources/${GS_SHADER_NAME})
endif()	

if (CMAKE_RELEASE)
	if (APPLE)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
	endif()
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -Ofast")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -Ofast")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -Ofast")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    	string(REGEX REPLACE "/W[0-4]" "/W4 /Zi" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  	else()
    	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /Zi")
  	endif()
endif()


if (APPLE)
	set_source_files_properties(${ICON_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
	file(COPY ${ICON_PATH} DESTINATION "${PROJECT_NAME}.app/Contents/Resources")
	file(COPY ${VS_SHADER_PATH} DESTINATION "${PROJECT_NAME}.app/Contents/Resources")
	file(COPY ${FS_SHADER_PATH} DESTINATION "${PROJECT_NAME}.app/Contents/Resources")
	file(COPY ${GS_SHADER_PATH} DESTINATION "${PROJECT_NAME}.app/Contents/Resources")

  	add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${ICON_PATH} main.cpp)				# Create executable with the name of a project add MACOSX_BUNDLE
  	set_target_properties(${PROJECT_NAME} PROPERTIES
	    BUNDLE True
	    MACOSX_BUNDLE_GUI_IDENTIFIER choodick.com.${PROJECT_NAME}
	    MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
	    MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
	    MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
	    MACOSX_BUNDLE_ICONFILE ${ICON_NAME}
	)
endif()

if (WIN32)
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
    endif(MINGW)

	add_executable(${PROJECT_NAME} WIN32 main.cpp ${APP_ICON_RESOURCE_WINDOWS})						# Create executable with the name of a project add WIN32
endif()

add_subdirectory(window_handler)										# Add widnow_handler sub directory in order to load library

target_include_directories(${PROJECT_NAME} PUBLIC window_handler/)		# Link include directory 
target_link_directories(${PROJECT_NAME} PUBLIC window_handler/)			# Link directories for libraries
target_link_libraries(${PROJECT_NAME} window_handler)					# Link libraries to the project

if (CMAKE_RELEASE AND CMAKE_UPX_COMPRESS)
	message(STATUS "Stripping with ${CMAKE_STRIP}")
	message(STATUS "Applying UPX compression")
	if (APPLE)
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${PROJECT_NAME}> && upx -9 $<TARGET_FILE:${PROJECT_NAME}>)
	else ()
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} --strip-all $<TARGET_FILE:${PROJECT_NAME}> && upx -9 $<TARGET_FILE:${PROJECT_NAME}>)
	endif ()
elseif (CMAKE_RELEASE)
	message(STATUS "Stripping with ${CMAKE_STRIP}")
	if (APPLE)
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${PROJECT_NAME}>)
	else ()
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} --strip-all $<TARGET_FILE:${PROJECT_NAME}>)
	endif ()
elseif (CMAKE_UPX_COMPRESS)
	message(STATUS "Applying UPX compression")
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND upx -9 $<TARGET_FILE:${PROJECT_NAME}>)
endif()