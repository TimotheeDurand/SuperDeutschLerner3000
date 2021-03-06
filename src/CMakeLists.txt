file(GLOB_RECURSE SOURCE_FILES "*.cpp")
file(GLOB_RECURSE HEADER_FILES "*.h" "*.hpp")
file(GLOB_RECURSE LIBS_SOURCES "../libs/*.hpp")
file(GLOB_RECURSE MAIN "main.cpp")
file(GLOB_RECURSE MAINCLI "mainCLI.cpp")
file(GLOB_RECURSE RESOURCES "${CMAKE_SOURCE_DIR}/resources/*.qrc")
file(GLOB_RECURSE RESOURCES_MS "${CMAKE_SOURCE_DIR}/resources/*.rc")
list(REMOVE_ITEM SOURCE_FILES ${MAIN})
list(REMOVE_ITEM SOURCE_FILES ${MAINCLI})

file(GLOB_RECURSE EXAMPLES_LESSONS "${PROJECT_SOURCE_DIR}/examples/*.les")

add_executable (SuperDeutschLerner3000CLI mainCLI.cpp)
if (WIN32)
	add_executable (SuperDeutschLerner3000 main.cpp ${RESOURCES_MS})
else()
	add_executable (SuperDeutschLerner3000 main.cpp)
endif()
add_library (DeutschLernerLibrary ${SOURCE_FILES} ${HEADER_FILES} ${LIBS_SOURCES} ${RESOURCES})
target_link_libraries (SuperDeutschLerner3000 DeutschLernerLibrary)
target_link_libraries (SuperDeutschLerner3000CLI DeutschLernerLibrary)

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
	#copy lesson files
	add_custom_command(TARGET SuperDeutschLerner3000 POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  
			${EXAMPLES_LESSONS}
			${EXECUTABLE_OUTPUT_PATH})    

	#copy Qt Dlls
	add_custom_command(
    TARGET SuperDeutschLerner3000 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Core> $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE:Qt5::Svg>
        $<TARGET_FILE_DIR:SuperDeutschLerner3000>)
		
	#copy lesson files
	add_custom_command(TARGET SuperDeutschLerner3000CLI POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different  
			${EXAMPLES_LESSONS}
			${EXECUTABLE_OUTPUT_PATH})    

	#copy Qt Dlls
	add_custom_command(
    TARGET SuperDeutschLerner3000CLI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Core>
        $<TARGET_FILE_DIR:SuperDeutschLerner3000CLI>)

	set_target_properties(SuperDeutschLerner3000 PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")
	set_target_properties(SuperDeutschLerner3000CLI PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON) # Find includes in corresponding build directories
set(CMAKE_AUTOMOC ON) # Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTORCC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Svg REQUIRED)
target_link_libraries(DeutschLernerLibrary Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Svg)

