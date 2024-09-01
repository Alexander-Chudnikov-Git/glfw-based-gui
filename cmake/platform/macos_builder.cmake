set(ICON_NAME "icon.icns")
set(ICON_PATH ${PROJECT_SOURCE_DIR}/resources/icons/macos/${ICON_NAME})

set(VS_SHADER_NAME "cgui_tri_vert.vs")
set(VS_SHADER_PATH ${PROJECT_SOURCE_DIR}/resources/${VS_SHADER_NAME})

set(FS_SHADER_NAME "cgui_tri_frag.fs")
set(FS_SHADER_PATH ${PROJECT_SOURCE_DIR}/resources/${FS_SHADER_NAME})

set(GS_SHADER_NAME "cgui_tri_geom.gs")
set(GS_SHADER_PATH ${PROJECT_SOURCE_DIR}/resources/${GS_SHADER_NAME})

add_compile_options(
	-fvisibility=hidden
	-pedantic
	-Wall
	-Wextra
	-Wcast-align
	-Wcast-qual
	-Wctor-dtor-privacy
	-Wdisabled-optimization
	-Wformat=2
	-Winit-self
	-Wmissing-declarations
	-Wmissing-include-dirs
	-Woverloaded-virtual
	-Wredundant-decls
	-Wshadow
	-Wsign-promo
	-Wstrict-overflow=5
	-Wswitch-default
	-Wundef
	-Werror
	-Wno-unused
	-Ofast
)

set_source_files_properties(${ICON_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

file(COPY ${ICON_PATH} DESTINATION "${PROJECT_NAME}.app/Contents/Resources")
file(COPY ${VS_SHADER_PATH} DESTINATION "${PROJECT_NAME}.app/Contents/Resources")
file(COPY ${FS_SHADER_PATH} DESTINATION "${PROJECT_NAME}.app/Contents/Resources")
file(COPY ${GS_SHADER_PATH} DESTINATION "${PROJECT_NAME}.app/Contents/Resources")

add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${ICON_PATH} main.cpp) # Create target build for MACOSX_BUNDLE excutable
set_target_properties(${PROJECT_NAME} PROPERTIES
	BUNDLE True
	MACOSX_BUNDLE_GUI_IDENTIFIER choodick.com.${PROJECT_NAME}
	MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
	MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
	MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
	MACOSX_BUNDLE_ICONFILE ${ICON_NAME}
)
