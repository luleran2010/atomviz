#include <catch2/catch_test_macros.hpp>

#include <string>
#include <filesystem>

#include "Atoms.h"
#include "PoscarParser.h"

TEST_CASE("test_parsers", "[test_parsers]") {
    std::string filename = RESOURCE_DIR + std::string("Zn.vasp");
    PoscarParser parser(filename);
    std::optional<Atoms> atoms = parser.parse();
    REQUIRE(atoms->size() == 4);
}