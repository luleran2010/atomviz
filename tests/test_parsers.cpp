#include <catch2/catch_test_macros.hpp>

#include <string>
#include <iostream>
#include <filesystem>
#include <eigen3/Eigen/Dense>

#include "Atoms.h"
#include "PoscarParser.h"

TEST_CASE("test_parsers", "[test_parsers]") {
    std::string filename = RESOURCE_DIR + std::string("Zn.vasp");
    PoscarParser parser(filename);
    Atoms atoms = parser.parse().value();
    REQUIRE(atoms.size() == 4);
    Eigen::MatrixX3f positions = atoms.positions();
    // check the shape of the position matrix
    REQUIRE(positions.rows() == 4);
    REQUIRE(positions.cols() == 3);
    // test the position matrix with the way of operator[] of atoms
    std::cout << "First few positions:\n";
    for (int i = 0; i < 4; i++) {
        Eigen::Vector3f position = atoms[i].position().transpose();
        REQUIRE(position(0) == positions(i, 0));
        REQUIRE(position(1) == positions(i, 1));
        REQUIRE(position(2) == positions(i, 2));
    }
}