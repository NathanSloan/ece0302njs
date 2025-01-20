#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include <iostream>
#include "bitarray.hpp"

TEST_CASE("Test bitarray construction with empty string", "[bitarray]")
{
    std::string s("");
    Bitarray b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE("Test toggle with bitarray default construction", "[bitarray]")
{
    Bitarray b;
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    for (int i = 0; i < b.size(); i++)
    {
        b.toggle(i);
        REQUIRE(b.test(i) == 1);
    }
    REQUIRE(b.asString().compare("11111111") == 0); // after all toggle should be 11111111
}

TEST_CASE("Test set with bitarray string construction", "[bitarray]")
{
    std::string s("00101");
    Bitarray b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
    b.set(1);
    REQUIRE(b.asString().compare(s) != 0);
    REQUIRE(b.asString().compare("01101") == 0);
    REQUIRE(b.good());
}

TEST_CASE("Test reset with bitarray string construction", "[bitarray]")
{
    std::string s("10101");
    Bitarray b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
    b.reset(0);
    REQUIRE(b.asString().compare(s) != 0);
    REQUIRE(b.asString().compare("00101") == 0);
    REQUIRE(b.good());
}
TEST_CASE("Test set and reset with default construction", "[bitarray]")
{
    Bitarray b;
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    for (int i = 0; i < b.size(); i++)
    {
        b.set(i);
        REQUIRE(b.test(i) == 1);
    }
    REQUIRE(b.asString().compare("11111111") == 0); // after all toggle should be 11111111
    for (int i = 0; i < b.size(); i += 2)
    {
        b.reset(i);
        REQUIRE(b.test(i) == 0);
    }
    REQUIRE(b.asString().compare("01010101") == 0); // after all toggle should be 11111111
    REQUIRE(b.good());
}

TEST_CASE("Test bitarray default construction", "[bitarray]")
{

    Bitarray b;
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

TEST_CASE("Test bitarray construction with asString", "[bitarray]")
{
    Bitarray b;
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE("Test bitarray construction size", "[bitarray]")
{
    Bitarray b(64);
    std::string s(64, '0');
    REQUIRE(b.size() == 64);
    REQUIRE(b.good());
}

TEST_CASE("Test bitarray construction string", "[bitarray]")
{
    std::string s("00101110000011000001101000001");
    Bitarray b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE("Test bitarray construction invalid string", "[bitarray]")
{
    std::string s("00101110000011002001101000001");
    Bitarray b(s);
    REQUIRE_FALSE(b.good());
}

TEST_CASE("Test set", "[bitarray]")
{
    std::string s("00010001");
    Bitarray b;
    b.set(3);
    b.set(7);
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE("Test set with size init", "[bitarray]")
{
    std::string s("00010");
    Bitarray b(5);
    b.set(3);
    REQUIRE(b.size() == 5);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE("Test combined", "[bitarray]")
{
    std::string s((1 << 15) + 3, '0');
    Bitarray b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);

    for (int i = 1; i < (1 << 10); i++)
    {
        b.set(i);
        b.reset(i + (1 << 10));
        b.toggle(i + (1 << 11));
        REQUIRE(b.good());
        REQUIRE(b.test(i));
        REQUIRE_FALSE(b.test(i + (1 << 10)));
        REQUIRE(((b.test(i + (1 << 11)) == true && s.at(i + (1 << 11)) == '0') || (b.test(i + (1 << 11)) == false && s.at(i + (1 << 11)) == '1')));
    }
}
