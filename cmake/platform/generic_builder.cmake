# Make sure that we are not building in top level directory

message(STATUS "CXX compiler:      ${CMAKE_CXX_COMPILER_ID}")

if(NOT CMAKE_RELEASE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

if(MACOS)
    include(cmake/platform/macos_builder.cmake)
elseif(LINUX)
    include(cmake/platform/linux_builder.cmake)
elseif(WIN32)
    include(cmake/platform/windows_builder.cmake)
else()
    message(FATAL_ERROR "Unsupported OS: ${CMAKE_SYSTEM_NAME}")
endif()

add_subdirectory(window_handler) # Add widnow_handler sub directory in order to load library

target_include_directories(${PROJECT_NAME} PUBLIC window_handler/) # Link include directory
target_link_directories(${PROJECT_NAME} PUBLIC window_handler/) # Link directories for libraries
target_link_libraries(${PROJECT_NAME} window_handler) # Link libraries to the project

if(CMAKE_RELEASE AND CMAKE_UPX_COMPRESS)
	message(STATUS "Stripping with ${CMAKE_STRIP}")
	message(STATUS "Applying UPX compression")

	if(APPLE)
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${PROJECT_NAME}> && upx -9 $<TARGET_FILE:${PROJECT_NAME}>)
	else()
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} --strip-all $<TARGET_FILE:${PROJECT_NAME}> && upx -9 $<TARGET_FILE:${PROJECT_NAME}>)
	endif()

elseif(CMAKE_RELEASE)
	message(STATUS "Stripping with ${CMAKE_STRIP}")

	if(APPLE)
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${PROJECT_NAME}>)
	else()
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_STRIP} --strip-all $<TARGET_FILE:${PROJECT_NAME}>)
	endif()

elseif(CMAKE_UPX_COMPRESS)
	message(STATUS "Applying UPX compression")

	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND upx -9 $<TARGET_FILE:${PROJECT_NAME}>)
endif()
