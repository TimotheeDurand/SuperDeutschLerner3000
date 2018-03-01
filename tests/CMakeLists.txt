file(GLOB_RECURSE TEST_SOURCES "*.cpp")
add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (Test ${TEST_SOURCES} catch.hpp)
target_link_libraries (Test DeutschLernerLibrary)