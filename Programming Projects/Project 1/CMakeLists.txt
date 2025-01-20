cmake_minimum_required(VERSION 3.10)
project(P1)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_bitarray.cpp bitarray.hpp bitarray.cpp)

# create unittests
add_executable(test-bitarray catch.hpp ${SOURCE})

enable_testing()

# unit tests
add_test(test-bitarray test-bitarray)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/p1_bitarray.zip" --format=zip
       ${SOURCE}
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
     