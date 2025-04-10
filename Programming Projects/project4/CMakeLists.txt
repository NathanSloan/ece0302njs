cmake_minimum_required(VERSION 3.10)
project(P4)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# build the image library
ADD_SUBDIRECTORY(lib)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

# build the compare program
ADD_EXECUTABLE(compare compare.cpp)
TARGET_LINK_LIBRARIES(compare image)

set(QUEUE_SOURCE
  list.hpp list.tpp queue.hpp queue.tpp)

if(EXISTS "${PROJECT_SOURCE_DIR}/Node.tpp" AND EXISTS "${PROJECT_SOURCE_DIR}/Node.hpp")
    set(QUEUE_SOURCE ${QUEUE_SOURCE} Node.tpp Node.hpp)
endif()

set(TEST_SOURCE
  test_queue.cpp)

set(PATHFINDER_SOURCE pathfinder.cpp)

set(SOURCE ${QUEUE_SOURCE} ${TEST_SOURCE} ${PATHFINDER_SOURCE})

# create unittests
add_executable(test-queue catch.hpp abstract_list.hpp abstract_queue.hpp ${QUEUE_SOURCE} ${TEST_SOURCE})
TARGET_LINK_LIBRARIES(test-queue)

# build executable
add_executable(pathfinder abstract_list.hpp abstract_queue.hpp ${QUEUE_SOURCE} ${PATHFINDER_SOURCE})
TARGET_LINK_LIBRARIES(pathfinder image)

# some simple tests
enable_testing()
add_test(NAME Pathfinder:test-queue COMMAND test-queue)

add_test(NAME SETUP:test00 COMMAND pathfinder ${CMAKE_SOURCE_DIR}/tests/maze00.png output00.png)
add_test(NAME Pathfinder:test00-compare COMMAND compare ${CMAKE_SOURCE_DIR}/tests/output00.png output00.png)
set_tests_properties(Pathfinder:test00-compare PROPERTIES FIXTURES_REQUIRED TEST0)
set_tests_properties(SETUP:test00 PROPERTIES FIXTURES_SETUP TEST0)

add_test(NAME SETUP:test01 COMMAND pathfinder ${CMAKE_SOURCE_DIR}/tests/maze01.png output01.png)
add_test(NAME Pathfinder:test01-compare COMMAND compare ${CMAKE_SOURCE_DIR}/tests/output01.png output01.png)
set_tests_properties(Pathfinder:test01-compare PROPERTIES FIXTURES_REQUIRED TEST1)
set_tests_properties(SETUP:test01 PROPERTIES FIXTURES_SETUP TEST1)

add_test(NAME SETUP:test02 COMMAND pathfinder ${CMAKE_SOURCE_DIR}/tests/maze02.png output02.png)
add_test(NAME Pathfinder:test02-compare COMMAND compare ${CMAKE_SOURCE_DIR}/tests/output02.png output02.png)
set_tests_properties(Pathfinder:test02-compare PROPERTIES FIXTURES_REQUIRED TEST2)
set_tests_properties(SETUP:test02 PROPERTIES FIXTURES_SETUP TEST2)

add_test(NAME SETUP:test03 COMMAND pathfinder ${CMAKE_SOURCE_DIR}/tests/maze03.png output03.png)
add_test(NAME Pathfinder:test03-compare COMMAND compare ${CMAKE_SOURCE_DIR}/tests/output03.png output03.png)
set_tests_properties(Pathfinder:test03-compare PROPERTIES FIXTURES_REQUIRED TEST3)
set_tests_properties(SETUP:test03 PROPERTIES FIXTURES_SETUP TEST3)

add_test(NAME Pathfinder:test-invalid1 COMMAND pathfinder ${CMAKE_SOURCE_DIR}/tests/maze00_extra_color.png output00_extra_color.png)
add_test(NAME Pathfinder:test-invalid2 COMMAND pathfinder ${CMAKE_SOURCE_DIR}/tests/maze00_extra_start.png output00_extra_start.png)
add_test(NAME Pathfinder:test-invalid3 COMMAND pathfinder ${CMAKE_SOURCE_DIR}/tests/maze00_no_start.png output00_no_start.png)

# specify fail for invalid input tests
set_tests_properties(Pathfinder:test-invalid1 
              Pathfinder:test-invalid2 
              Pathfinder:test-invalid3 
              PROPERTIES WILL_FAIL TRUE)

# set timeout (in seconds) for solving mazes
set_tests_properties(SETUP:test00 SETUP:test01 SETUP:test02 SETUP:test03 PROPERTIES TIMEOUT 180)

# run tests in order
set_tests_properties(Pathfinder:test00-compare 
              Pathfinder:test01-compare 
              Pathfinder:test02-compare
              Pathfinder:test03-compare 
              PROPERTIES RUN_SERIAL TRUE)

add_custom_target(submission COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/p4_pathfinder.zip" --format=zip
  ${SOURCE}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
