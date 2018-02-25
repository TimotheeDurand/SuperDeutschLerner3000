cmake_minimum_required(VERSION 3.2)
project(SuperDeutschLerner3000 C CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/)
set(EXECUTABLE_OUTPUT_PATH ../bin/)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "src/*.h")

add_executable(SuperDeutschLerner3000 ${SOURCE_FILES} ${HEADER_FILES})

# Needed for having the good directory tree in the Visual studio project
foreach(source IN LISTS SOURCE_FILES)
    get_filename_component(source_path "${source}" PATH)
	file(RELATIVE_PATH source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}/src" "${source_path}")
    string(REPLACE "/" "\\" source_path_msvc "${source_path_rel}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

foreach(header IN LISTS HEADER_FILES)
    get_filename_component(header_path "${header}" PATH)
	file(RELATIVE_PATH header_path_rel "${CMAKE_CURRENT_SOURCE_DIR}/src" "${header_path}")
    string(REPLACE "/" "\\" header_path_msvc "${header_path_rel}")
    source_group("${header_path_msvc}" FILES "${header}")
endforeach()

target_link_libraries(SuperDeutschLerner3000 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})