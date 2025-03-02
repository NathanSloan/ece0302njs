#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "sorted_list.hpp"
#include "list.hpp"

/* Provided tests */
TEST_CASE("SortedList: Testing size", "[sorted list]") {
  SortedList<char> lst;

  REQUIRE(lst.isEmpty());
  REQUIRE(lst.getLength() == 0);

  lst.insert('b');
  REQUIRE(!lst.isEmpty());
  REQUIRE(lst.getLength() == 1);

  lst.insert('a');
  REQUIRE(lst.getLength() == 2);

  lst.removeAt(0);
  REQUIRE(lst.getLength() == 1);

  lst.removeAt(0);
  REQUIRE(lst.getLength() == 0);
  REQUIRE(lst.isEmpty());
}


TEST_CASE("SortedList: Testing insert", "[sorted list]") {
  SortedList<char> lst;

  char c = 'a';
  while (c <= 'z') {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == 26);

  bool getEntryCheck;
  for (int i = 0; i < 26; ++i) {
    getEntryCheck = (lst.getEntry(i) == 'a' + i);
    if (!getEntryCheck) {
      break;
    }
  }
  REQUIRE(getEntryCheck);
}


TEST_CASE("SortedList: Testing remove", "[sorted list]") {
  SortedList<char> lst;

  char c = 'a';
  int size = 10;
  while (c < 'a'+size) {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == size);

  lst.remove('c');
  REQUIRE(lst.getLength() == size-1);
  REQUIRE(lst.getEntry(2) == 'd');

  lst.remove('e');
  REQUIRE(lst.getLength() == size-2);
  REQUIRE(lst.getEntry(5) == 'h');

  lst.remove('a');
  REQUIRE(lst.getLength() == size-3);
  REQUIRE(lst.getEntry(0) == 'b');
}


TEST_CASE("SortedList: Testing getPosition", "[sorted list]") {
  SortedList<char> lst;
  
  lst.insert('a');
  lst.insert('d');
  lst.insert('e');
  lst.insert('c');
  lst.insert('b');

  REQUIRE(lst.getPosition('a') == 0);
  REQUIRE(lst.getPosition('b') == 1);
  REQUIRE(lst.getPosition('c') == 2);
  REQUIRE(lst.getPosition('d') == 3);
  REQUIRE(lst.getPosition('e') == 4);
}


TEST_CASE("Testing init from list", "[sorted list]") {
  List<char> unsorted;
  
  unsorted.insert(0,'a');
  unsorted.insert(1,'d');
  unsorted.insert(2,'e');
  unsorted.insert(3,'c');
  unsorted.insert(4,'b');

  SortedList<char> sorted(unsorted);

  REQUIRE(sorted.getPosition('a') == 0);
  REQUIRE(sorted.getPosition('b') == 1);
  REQUIRE(sorted.getPosition('c') == 2);
  REQUIRE(sorted.getPosition('d') == 3);
  REQUIRE(sorted.getPosition('e') == 4);
}


TEST_CASE("SortedList: Testing list exceptions", "[list]") {
  List<char> lst;

  REQUIRE_THROWS_AS(lst.remove(0), std::out_of_range);
  REQUIRE_THROWS_AS(lst.insert(1,'a'), std::out_of_range);
  REQUIRE_THROWS_AS(lst.getEntry(0), std::out_of_range);
  REQUIRE_THROWS_AS(lst.setEntry(0,'a'), std::out_of_range);

  lst.insert(0,'a');
  lst.insert(1,'b');

  REQUIRE_THROWS_AS(lst.remove(2), std::out_of_range);
  REQUIRE_THROWS_AS(lst.insert(3,'c'), std::out_of_range);
  REQUIRE_THROWS_AS(lst.getEntry(2), std::out_of_range);
  REQUIRE_THROWS_AS(lst.setEntry(2,'c'), std::out_of_range);

}

/* Your tests here */