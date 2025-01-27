cmake_minimum_required(VERSION 3.10)
project(bags)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIMITED_SIZE_BAG_SOURCE abstract_bag.hpp limited_size_bag.hpp limited_size_bag.tpp test_limited_size_bag.cpp)
set(DYNAMIC_BAG_SOURCE abstract_bag.hpp dynamic_bag.hpp dynamic_bag.tpp test_dynamic_bag.cpp)

# create unittests
add_executable(test-limited-size-bag catch.hpp ${LIMITED_SIZE_BAG_SOURCE})
add_executable(test-dynamic-bag catch.hpp ${DYNAMIC_BAG_SOURCE})

enable_testing()

# unit tests
add_test(test-limited-size-bag test-limited-size-bag) 
add_test(test-dynamic-bag test-dynamic-bag)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/problem_bags.zip" --format=zip
       ${DYNAMIC_BAG_SOURCE}
       ${LIMITED_SIZE_BAG_SOURCE}
       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
      