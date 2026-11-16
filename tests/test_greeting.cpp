#include <catch2/catch_test_macros.hpp>

#include "greeting.h"

TEST_CASE("greeting defaults to World") { REQUIRE(greeting() == "Hello, World!"); }

TEST_CASE("greeting uses the given name") { REQUIRE(greeting("Ray") == "Hello, Ray!"); }
