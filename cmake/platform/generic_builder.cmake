# Make sure that we are not building in top level directory

if(LINUX)
        include(cmake/utils/get_linux_kernel.cmake)

elseif(MACOS)

elseif(WIN32)

else()
    message(FATAL_ERROR "Unsupported OS: ${CMAKE_SYSTEM_NAME}")
endif()
