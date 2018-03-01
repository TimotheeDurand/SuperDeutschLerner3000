add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (Test test.cpp catch.hpp)
target_link_libraries (Test DeutschLernerLibrary)