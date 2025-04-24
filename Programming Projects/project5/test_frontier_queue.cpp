#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "frontier_queue.hpp"

TEST_CASE("Simple push test", "[frontier_queue]")
{
    frontier_queue<int> fq;
    REQUIRE(fq.empty());

    fq.push(1, 0, 1);

    REQUIRE_FALSE(fq.empty());
    REQUIRE(fq.contains(1));
}

TEST_CASE("Simple contains test", "[frontier_queue]")
{
    frontier_queue<int> fq;

    REQUIRE_FALSE(fq.contains(1));
    REQUIRE_FALSE(fq.contains(2));

    fq.push(1, 1, 1);
    fq.push(2, 2, 2);

    REQUIRE(fq.contains(1));
    REQUIRE(fq.contains(2));
    REQUIRE_FALSE(fq.contains(3));
}

TEST_CASE("Simple pop test", "[frontier_queue]")
{
    frontier_queue<int> fq;

    fq.push(1, 1, 1);

    State<int> state = fq.pop();
    REQUIRE(state.getValue() == 1);
    REQUIRE(state.getPathCost() == 1);
    REQUIRE(state.getFCost() == 2);
    REQUIRE(fq.empty());
}

TEST_CASE("Simple replaceif test", "[frontier_queue]")
{
    frontier_queue<int> fq;

    fq.push(1, 100, 100);

    fq.replaceif(1, 1);
    State<int> state = fq.pop();
    REQUIRE(state.getValue() == 1);
    REQUIRE(state.getPathCost() == 1);
    REQUIRE(state.getFCost() == 101);
}

/* Your test cases here */

TEST_CASE("frontier_queue")
{
    frontier_queue<int> fq;

    REQUIRE(fq.empty());

    fq.push(1, 1, 1);
    REQUIRE_FALSE(fq.empty());
    REQUIRE(fq.contains(1));

    fq.pop();
    REQUIRE(fq.empty());
    REQUIRE_FALSE(fq.contains(1));
}