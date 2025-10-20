#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../src/magazine_clippings.hpp"

std::string readFile(const std::string& filename) {
    std::ifstream file;

    file.open(filename);
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    file.open("../" + filename);
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    return "";
}

TEST_CASE("canCreateNote functionality") {
    SECTION("basic cases") {
        REQUIRE(canCreateNote("a", {"a"}) == true);
        REQUIRE(canCreateNote("a", {"b"}) == false);
        REQUIRE(canCreateNote("abc", {"a", "b", "c"}) == true);
    }

    SECTION("case and whitespace") {
        REQUIRE(canCreateNote("A", {"a"}) == true);
        REQUIRE(canCreateNote("a b c", {"abc"}) == true);
        REQUIRE(canCreateNote("", {"any", "text"}) == true);
    }

    SECTION("character limits") {
        REQUIRE(canCreateNote("aa", {"a"}) == false);
        REQUIRE(canCreateNote("Hello", {"olleH"}) == true);
    }

    SECTION("complex sentences") {
        REQUIRE(canCreateNote("The bird is red!", {"I write a lot.", "To and fro.", "Here be deadly dragons!"}) == true);
        REQUIRE(canCreateNote("Hello; world.", {"Hello world"}) == false);
    }
}

TEST_CASE("Shakespeare stress test") {
    std::string othello = readFile("plays/othello.txt");
    std::string romeo = readFile("plays/romeo_and_juliet.txt");

    SECTION("character analysis") {
        REQUIRE(!othello.empty());
        REQUIRE(!romeo.empty());
        REQUIRE(othello.length() > romeo.length());
    }

    SECTION("can we create Romeo and Juliet from Othello") {
        bool result = canCreateNote(romeo, {othello});
        std::cout << "\nOthello: " << othello.length() << " chars" << std::endl;
        std::cout << "Romeo and Juliet: " << romeo.length() << " chars" << std::endl;
        std::cout << "Can create Romeo and Juliet from Othello: " << (result ? "YES" : "NO") << std::endl;
    }
}

TEST_CASE("Performance benchmarks", "[benchmark]") {
    std::string othello = readFile("plays/othello.txt");
    std::string romeo = readFile("plays/romeo_and_juliet.txt");

    BENCHMARK("full Shakespeare comparison") {
        return canCreateNote(romeo, {othello});
    };

    BENCHMARK("small note (100 chars)") {
        std::string note = romeo.substr(0, 100);
        return canCreateNote(note, {othello});
    };

    BENCHMARK("medium note (1000 chars)") {
        std::string note = romeo.substr(0, 1000);
        return canCreateNote(note, {othello});
    };
}