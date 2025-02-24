cmake_minimum_required(VERSION 3.10)
project(sorting)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_sort.cpp sort.hpp list.hpp list.tpp)

# include Node if present
if(EXISTS "${PROJECT_SOURCE_DIR}/Node.tpp" AND EXISTS "${PROJECT_SOURCE_DIR}/Node.hpp")
    set(SOURCE ${SOURCE} Node.tpp Node.hpp)
endif()

# create unittests
add_executable(test-sort catch.hpp abstract_list.hpp ${SOURCE})

enable_testing()

# unit tests
add_test(test-sort test-sort)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/problem_sorting.zip" --format=zip
       ${SOURCE}
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
     
