#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "list.hpp"
#include "sort.hpp"

/* Provided test cases */
TEST_CASE("Sort: Test move entry", "[sorting]")
{
  List<int> lst;

  lst.insert(0, 100);
  lst.insert(1, 4);
  lst.insert(2, 10);
  lst.insert(3, 25);
  lst.insert(4, 11);

  // move forward
  lst.moveEntry(0, 2);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(0) == 4);
  REQUIRE(lst.getEntry(1) == 10);
  REQUIRE(lst.getEntry(2) == 100);
  REQUIRE(lst.getEntry(3) == 25);
  REQUIRE(lst.getEntry(4) == 11);

  // move backward
  lst.moveEntry(4, 0);

  REQUIRE(lst.getLength() == 5);
  REQUIRE(lst.getEntry(0) == 11);
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getEntry(2) == 10);
  REQUIRE(lst.getEntry(3) == 100);
  REQUIRE(lst.getEntry(4) == 25);
}

TEST_CASE("Sort: Integer sorting", "[sorting]")
{

  List<int> lst;

  lst.insert(0, 100);
  lst.insert(1, 4);
  lst.insert(2, 10);
  lst.insert(3, 25);
  lst.insert(4, 11);

  quick_sort(lst, 0, lst.getLength() - 1);

  // check sorted list
  REQUIRE(lst.getEntry(0) == 4);
  REQUIRE(lst.getEntry(1) == 10);
  REQUIRE(lst.getEntry(2) == 11);
  REQUIRE(lst.getEntry(3) == 25);
  REQUIRE(lst.getEntry(4) == 100);
}

/* Your test cases here */