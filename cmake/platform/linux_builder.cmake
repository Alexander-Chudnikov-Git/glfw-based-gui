include(cmake/utils/get_linux_kernel.cmake)

set(APPLICATION_NAME "glfw_based_gui.desktop")
set(APPLICATION_PATH ${PROJECT_SOURCE_DIR}/resources/${APPLICATION_NAME})

set(ICON_FOLDER ${PROJECT_SOURCE_DIR}/resources/icons/linux/)

set(VS_SHADER_NAME "cgui_tri_vert.vs")
set(VS_SHADER_PATH ${PROJECT_SOURCE_DIR}/resources/${VS_SHADER_NAME})

set(FS_SHADER_NAME "cgui_tri_frag.fs")
set(FS_SHADER_PATH ${PROJECT_SOURCE_DIR}/resources/${FS_SHADER_NAME})

set(GS_SHADER_NAME "cgui_tri_geom.gs")
set(GS_SHADER_PATH ${PROJECT_SOURCE_DIR}/resources/${GS_SHADER_NAME})

add_compile_options(
    -fvisibility=hidden
    -fsanitize=address
    -pedantic
    -Wall
    -Wextra
    -Wcast-align
    -Wcast-qual
    -Wctor-dtor-privacy
    -Wdisabled-optimization
    -Wformat=2
    -Winit-self
    -Wlogical-op
    -Wmissing-declarations
    -Wmissing-include-dirs
    -Wnoexcept
    -Woverloaded-virtual
    -Wredundant-decls
    -Wshadow
    -Wsign-promo
    -Wstrict-null-sentinel
    -Wstrict-overflow=5
    -Wswitch-default
    -Wundef
    -Wno-unused-variable
    -Wno-error=redundant-decls
    -Ofast
)

# Add executable
add_executable(${PROJECT_NAME} main.cpp) # Create target build for UNIX excutable

# Optionally, you can configure installation paths for resources
install(FILES ${VS_SHADER_PATH} DESTINATION /usr/share/${PROJECT_NAME}/resources)
install(FILES ${FS_SHADER_PATH} DESTINATION /usr/share/${PROJECT_NAME}/resources)
install(FILES ${GS_SHADER_PATH} DESTINATION /usr/share/${PROJECT_NAME}/resources)

install(FILES ${APPLICATION_PATH} DESTINATION /usr/share/applications)
install(DIRECTORY ${ICON_FOLDER} DESTINATION /usr/share/icons/hicolor)

# Install the executable
install(TARGETS ${PROJECT_NAME} DESTINATION /usr/bin)
