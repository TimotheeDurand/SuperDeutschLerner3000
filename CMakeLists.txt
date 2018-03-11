cmake_minimum_required(VERSION 3.2)
project(SuperDeutschLerner3000 C CXX)

set(CMAKE_CXX_STANDARD 17)

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++17" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++17")
    endif()
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/)
set(EXECUTABLE_OUTPUT_PATH ../bin/)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory (src) 
add_subdirectory (tests)
add_test (NAME MyTest COMMAND Test)