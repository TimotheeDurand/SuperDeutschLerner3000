file(GLOB_RECURSE TEST_SOURCES "*.cpp")
file(GLOB_RECURSE LIBS_SOURCES "../libs/*.hpp")
add_definitions (-DBOOST_TEST_DYN_LINK)

set(CMAKE_INCLUDE_CURRENT_DIR ON) # Find includes in corresponding build directories
set(CMAKE_AUTOMOC ON) # Instruct CMake to run moc automatically when needed.

find_package(Qt5Core REQUIRED)

add_executable (Test ${TEST_SOURCES} ${LIBS_SOURCES})
target_link_libraries (Test DeutschLernerLibrary)