#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"

// force class expansion
template class ArrayList<int>;

TEST_CASE("Test isEmpty & getLength", "[ArrayList]")
{
  ArrayList<int> my_list;

  REQUIRE(my_list.isEmpty());
  REQUIRE(my_list.getLength() == 0);

  for (int i = 0; i < 7; i++)
  {
    my_list.insert(i, 7);
  }
  REQUIRE_FALSE(my_list.isEmpty());
  REQUIRE(my_list.getLength() == 7);
}

TEST_CASE("Test Clear", "[ArrayList]")
{
  ArrayList<int> my_list;
  for (int i = 0; i < 7; i++)
  {
    my_list.insert(i, i);
  }

  my_list.clear();

  REQUIRE(my_list.isEmpty()); // check that list is empty after clearing
}

TEST_CASE("Test getEntry", "[ArrayList]")
{
  ArrayList<int> my_list;
  for (int i = 0; i < 7; i++)
  {
    my_list.insert(i, i);
    REQUIRE(my_list.getEntry(i) == i);
  }
  REQUIRE_FALSE(my_list.getEntry(-1));
  REQUIRE_FALSE(my_list.getEntry(7));
}

TEST_CASE("Test Insert", "[ArrayList]")
{
  ArrayList<int> my_list;
  REQUIRE(my_list.isEmpty());
  REQUIRE(my_list.getLength() == 0);

  // out of bounds
  REQUIRE_FALSE(my_list.insert(-1, 7));
  REQUIRE_FALSE(my_list.insert(1, 7));

  // in bounds
  for (int i = 0; i < 127; i++)
  {
    REQUIRE(my_list.insert(i, i));
    REQUIRE(my_list.getEntry(i) == i);
  }
  for (int i = 127; i < 255; i++)
  {
    REQUIRE(my_list.insert(i, -i));
    REQUIRE(my_list.getEntry(i) == -i);
  }

  REQUIRE(my_list.getLength() == 255);
}

TEST_CASE("Test Remove", "[ArrayList]")
{
  ArrayList<int> my_list;
  REQUIRE(my_list.isEmpty());
  REQUIRE(my_list.getLength() == 0);

  for (int i = 0; i < 255; i++)
  {
    REQUIRE(my_list.insert(i, i));
    REQUIRE(my_list.getEntry(i) == i);
  }
  REQUIRE(my_list.getLength() == 255);

  // out of bounds
  REQUIRE_FALSE(my_list.remove(255));
  REQUIRE_FALSE(my_list.remove(-1));

  // in bounds

  // remove from end
  REQUIRE(my_list.remove(254));
  REQUIRE(my_list.getLength() == 254);

  // remove first, and check proper shift of elements
  REQUIRE(my_list.getEntry(0) == 0);
  REQUIRE(my_list.getEntry(1) == 1);
  REQUIRE(my_list.remove(0));
  REQUIRE(my_list.getEntry(0) == 1);
  REQUIRE(my_list.getLength() == 253);

  // remove first, and check proper shift, account for prior shift
  REQUIRE(my_list.getEntry(127) == 128);
  REQUIRE(my_list.getEntry(128) == 129);
  REQUIRE(my_list.remove(127));
  REQUIRE(my_list.getEntry(127) == 129);
  REQUIRE(my_list.getLength() == 252);
}

TEST_CASE("Test setEntry", "[ArrayList]")
{
  ArrayList<int> my_list;
  REQUIRE(my_list.isEmpty());
  REQUIRE(my_list.getLength() == 0);

  for (int i = 0; i < 255; i++)
  {
    REQUIRE(my_list.insert(i, i));
    REQUIRE(my_list.getEntry(i) == i);
  }

  REQUIRE(my_list.getLength() == 255);
  // start, end, middle
  my_list.setEntry(0, 7);
  REQUIRE(my_list.getEntry(0) == 7);
  my_list.setEntry(254, 7);
  REQUIRE(my_list.getEntry(254) == 7);
  my_list.setEntry(127, 7);
  REQUIRE(my_list.getEntry(127) == 7);

  // others should be unaffected
  REQUIRE_FALSE(my_list.getEntry(128) == 7);

  for (int i = 0; i < 255; i++)
  {
    my_list.setEntry(i, i + 1);
    REQUIRE(my_list.getEntry(i) == i + 1);
  }
}

TEST_CASE("Test swap", "[ArrayList]")
{
  ArrayList<int> my_list;
  ArrayList<int> other_list;
  REQUIRE(my_list.isEmpty());
  for (int i = 0; i < 10; i++)
  {
    my_list.insert(i, i + 1);
    other_list.insert(i, -(i + 1));
    REQUIRE_FALSE(my_list.getEntry(i) == -(i + 1));
    REQUIRE_FALSE(other_list.getEntry(i) == i + 1);
  }
  my_list.swap(other_list);
  for (int i = 0; i < 10; i++)
  {
    REQUIRE(my_list.getEntry(i) == -(i + 1));
    REQUIRE(other_list.getEntry(i) == i + 1);
  }
}

TEST_CASE("Test copy constructor", "[ArrayList]")
{
  ArrayList<int> my_list;
  REQUIRE(my_list.isEmpty());
  for (int i = 0; i < 10; i++)
  {
    my_list.insert(i, i);
  }
  ArrayList<int> other_list(my_list);
  for (int i = 0; i < 10; i++)
  {
    REQUIRE(other_list.getEntry(i) == i);
  }
  REQUIRE(other_list.getLength() == my_list.getLength());
}

TEST_CASE("Test = ", "[ArrayList]")
{
  ArrayList<int> my_list;
  ArrayList<int> other_list;
  REQUIRE(my_list.isEmpty());
  for (int i = 0; i < 10; i++)
  {
    my_list.insert(i, i);
    REQUIRE_FALSE(other_list.getEntry(i));
  }
  other_list = my_list;
  for (int i = 0; i < 10; i++)
  {
    REQUIRE(other_list.getEntry(i) == i);
  }
  ArrayList<int> another_list = other_list;
  for (int i = 0; i < 10; i++)
  {
    REQUIRE(another_list.getEntry(i) == i);
  }
}

TEST_CASE("Test", "[ArrayList]")
{

  ArrayList<int> list;
}
