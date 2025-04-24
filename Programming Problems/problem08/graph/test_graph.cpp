#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "graph.hpp"

TEST_CASE("Test Graph") {
  Graph<std::string> letterGraph;
  REQUIRE(letterGraph.getNumVertices() == 0);
  REQUIRE(letterGraph.getNumEdges() == 0);

  REQUIRE(letterGraph.add("A", "B"));
  REQUIRE(letterGraph.getNumVertices() == 2);
  REQUIRE(letterGraph.getNumEdges() == 1);

  REQUIRE(letterGraph.remove("A", "B"));
  REQUIRE(letterGraph.getNumVertices() == 0);
  REQUIRE(letterGraph.getNumEdges() == 0);

  REQUIRE_FALSE(letterGraph.remove("A", "B"));
  REQUIRE(letterGraph.add("A", "B"));
  REQUIRE_FALSE(letterGraph.add("A", "B"));
  REQUIRE(letterGraph.getNumVertices() == 2);
  REQUIRE(letterGraph.getNumEdges() == 1);

  REQUIRE(letterGraph.add("B", "C"));
  REQUIRE(letterGraph.getNumVertices() == 3);
  REQUIRE(letterGraph.getNumEdges() == 2);

  REQUIRE_FALSE(letterGraph.add("D", "E"));
  REQUIRE(letterGraph.getNumVertices() == 3);
  REQUIRE(letterGraph.getNumEdges() == 2);

  REQUIRE(letterGraph.add("C", "A"));
  REQUIRE(letterGraph.getNumVertices() == 3);
  REQUIRE(letterGraph.getNumEdges() == 3);
}
