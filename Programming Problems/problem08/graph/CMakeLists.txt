cmake_minimum_required(VERSION 3.10)
project(graph)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_graph.cpp graph.hpp graph.tpp) 

# create unittests
add_executable(test-graph catch.hpp abstract_graph.hpp ${SOURCE})

enable_testing()

add_test(test-graph test-graph)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/problem_graph.zip" --format=zip
       ${SOURCE}
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})  

