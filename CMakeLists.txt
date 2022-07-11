cmake_minimum_required(VERSION 3.21.1)									# Minimum requred CMake version

project(glfw-based-gui)													# Set name to the project

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)										# Set c++ standart to 20

set(ICON_NAME "icon.icns")
set(ICON_PATH ${PROJECT_SOURCE_DIR}/resources/${ICON_NAME})

set(VS_SHADER_NAME "cgui_tri_vert.vs")
set(VS_SHADER_PATH ${PROJECT_SOURCE_DIR}/resources/${VS_SHADER_NAME})

set(FS_SHADER_NAME "cgui_tri_frag.fs")
set(FS_SHADER_PATH ${PROJECT_SOURCE_DIR}/resources/${FS_SHADER_NAME})

set(GS_SHADER_NAME "cgui_tri_geom.gs")
set(GS_SHADER_PATH ${PROJECT_SOURCE_DIR}/resources/${GS_SHADER_NAME})

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -Ofast")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -Ofast")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused -Ofast")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    	string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  	else()
    	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
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
	add_executable(${PROJECT_NAME} WIN32 main.cpp)						# Create executable with the name of a project add WIN32
endif()

add_subdirectory(window_handler)										# Add widnow_handler subdirectory in order to load library

target_include_directories(${PROJECT_NAME} PUBLIC window_handler/)		# Link include directory 
target_link_directories(${PROJECT_NAME} PUBLIC window_handler/)			# Link directories for libraries
target_link_libraries(${PROJECT_NAME} window_handler)					# Link libraries to the project
