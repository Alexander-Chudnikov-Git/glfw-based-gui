cmake_minimum_required(VERSION 3.21.1)									# Minimum requred CMake version

project(glfw-based-gui)													# Set name to the project

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)										# Set c++ standart to 20

if (APPLE)
  	add_executable(${PROJECT_NAME} MACOSX_BUNDLE main.cpp)				# Create executable with the name of a project add MACOSX_BUNDLE
endif()

if (WIN32)
	add_executable(${PROJECT_NAME} WIN32 main.cpp)						# Create executable with the name of a project add WIN32
endif()

add_subdirectory(window_handler)										# Add widnow_handler subdirectory in order to load library

target_include_directories(${PROJECT_NAME} PUBLIC window_handler/)		# Link include directory 
target_link_directories(${PROJECT_NAME} PUBLIC window_handler/)			# Link directories for libraries
target_link_libraries(${PROJECT_NAME} window_handler)					# Link libraries to the project
# Ты пидор 