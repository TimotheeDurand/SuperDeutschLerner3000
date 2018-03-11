file(GLOB_RECURSE SOURCE_FILES "*.cpp")
file(GLOB_RECURSE HEADER_FILES "*.h" "*.hpp")
file(GLOB_RECURSE LIBS_SOURCES "../libs/*.hpp")
file(GLOB_RECURSE MAIN "main.cpp")
list(REMOVE_ITEM SOURCE_FILES ${MAIN})

file(GLOB_RECURSE EXAMPLES_LESSONS "${PROJECT_SOURCE_DIR}/examples/*.les")

add_executable (SuperDeutschLerner3000 main.cpp)

# Needed for having the good directory tree in the Visual studio project
foreach(source IN LISTS SOURCE_FILES)
    get_filename_component(source_path "${source}" PATH)
	file(RELATIVE_PATH source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${source_path}")
    string(REPLACE "/" "\\" source_path_msvc "${source_path_rel}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

foreach(header IN LISTS HEADER_FILES)
    get_filename_component(header_path "${header}" PATH)
	file(RELATIVE_PATH header_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${header_path}")
    string(REPLACE "/" "\\" header_path_msvc "${header_path_rel}")
    source_group("${header_path_msvc}" FILES "${header}")
endforeach()

if (MSVC_VERSION)
	add_custom_command(TARGET SuperDeutschLerner3000 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  
			${EXAMPLES_LESSONS}
			${EXECUTABLE_OUTPUT_PATH})         

	set_target_properties(SuperDeutschLerner3000 PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")
endif()

add_library (DeutschLernerLibrary ${SOURCE_FILES} ${HEADER_FILES} ${LIBS_SOURCES})

target_link_libraries (SuperDeutschLerner3000 DeutschLernerLibrary)