#include <catch2/catch_test_macros.hpp>

#include <string>
#include <iostream>
#include <filesystem>
#include <cmath>

#include "PeriodicTable.h"

TEST_CASE("test_ptable", "[test_ptable]") {
    Element element = PeriodicTable::getInstance().getElement(1);
    REQUIRE(element.symbol == "H");
    REQUIRE(element.name == "Hydrogen");
    REQUIRE(std::abs(element.atomicMass - 1.008f) < 0.001f);
    REQUIRE(std::abs(element.radius - 1.20f) < 0.001f);
    REQUIRE(element.color == 0xffffff);
}