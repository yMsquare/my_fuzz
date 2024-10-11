cmake_minimum_required(VERSION 3.19)
project(my_fuzz)

# Option to add coverage instrumentation
option(COVERAGE_INSTRUMENTATION "Add coverage instrumentation to generate coverage reports." OFF)
set(COVERAGE_FLAGS -fprofile-instr-generate -fcoverage-mapping)

#
enable_testing()
set(CXX_STANDARD 17)
add_subdirectory(fuzztest)


#add_subdirectory(lib/rapidjson)
#add third-party libraries:
#add_library(libname STATIC libpath/lib.cpp)
#target_include_directories(libname PUBLIC libname)

#include(GoogleTest)

fuzztest_setup_fuzzing_flags()

include_directories(ENV{HOME}/rapidjson/include)
add_executable(
    my_test
    my_test.cc
        #lib/stringcat.h
        include/rapidjson/document.h
        include/rapidjson/writer.h
        include/rapidjson/stringbuffer.h
)

link_fuzztest(my_test)
gtest_discover_tests(my_test)

# 添加rapidjson库
target_include_directories(my_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/rapidjson)