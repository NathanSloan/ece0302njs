#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "node.hpp"
#include "list.hpp"
#include "queue.hpp"

TEST_CASE("Node")
{
  Node<int> nodeA;
  nodeA.setItem(0);
  REQUIRE(nodeA.getItem() == 0);
  REQUIRE(nodeA.getNext() == nullptr);

  nodeA.setItem(493);
  REQUIRE(nodeA.getItem() == 493);

  Node<int> *nodeBPtr = new Node<int>(1000);
  nodeA.setNext(nodeBPtr);
  REQUIRE(nodeBPtr->getItem() == 1000);
  REQUIRE(nodeA.getNext() == nodeBPtr);
  REQUIRE(nodeBPtr->getNext() == nullptr);
}

TEST_CASE("List")
{
  List<int> listA;
  REQUIRE(listA.isEmpty());
  REQUIRE(listA.getLength() == 0);

  listA.insert(0, 151);
  REQUIRE_FALSE(listA.isEmpty());
  REQUIRE(listA.getLength() == 1);
  REQUIRE(listA.getEntry(0) == 151);

  listA.insert(1, 251);
  listA.insert(2, 386);
  listA.insert(3, 493);
  REQUIRE(listA.getLength() == 4);
  REQUIRE(listA.getEntry(2) == 386);

  listA.insert(2, 300);
  REQUIRE(listA.getLength() == 5);
  REQUIRE(listA.getEntry(1) == 251);
  REQUIRE(listA.getEntry(2) == 300);
  REQUIRE(listA.getEntry(3) == 386);

  listA.remove(2);
  REQUIRE(listA.getLength() == 4);
  REQUIRE(listA.getEntry(1) == 251);
  REQUIRE(listA.getEntry(2) == 386);

  List<int> listB(listA);
  REQUIRE(listB.getLength() == 4);
  REQUIRE(listB.getEntry(0) == 151);
  REQUIRE(listB.getEntry(3) == 493);

  listB.insert(4, 649);
  listB.insert(5, 721);
  REQUIRE(listB.getLength() == 6);
  REQUIRE(listB.getEntry(5) == 721);

  listA.swap(listB);
  REQUIRE(listA.getLength() == 6);
  REQUIRE(listA.getEntry(5) == 721);
  REQUIRE(listB.getLength() == 4);

  listB.clear();
  REQUIRE(listB.isEmpty());

  REQUIRE_THROWS_AS(listB.getEntry(1), std::range_error);
  REQUIRE_THROWS_AS(listB.insert(2, 9000), std::range_error);
  REQUIRE_THROWS_AS(listB.remove(2), std::range_error);
}

/* Provided test cases */
TEST_CASE("Queue: Testing Enqueue", "[queue]")
{
  Queue<int, List<int>> queue;

  REQUIRE(queue.isEmpty());
  queue.enqueue(12);
  REQUIRE_FALSE(queue.isEmpty());
}

/* Your test cases here */
TEST_CASE("Queue Test")
{
  Queue<int, List<int>> queue;
  queue.enqueue(151);
  queue.enqueue(251);
  queue.enqueue(386);

  REQUIRE(queue.peekFront() == 151);

  queue.dequeue();
  REQUIRE(queue.peekFront() == 251);

  queue.dequeue();
  REQUIRE(queue.peekFront() == 386);

  queue.dequeue();
  REQUIRE(queue.isEmpty());

  REQUIRE_THROWS_AS(queue.peekFront(), std::out_of_range);
  REQUIRE_THROWS_AS(queue.dequeue(), std::out_of_range);
}