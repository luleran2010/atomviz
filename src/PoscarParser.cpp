#include <fstream>
#include <sstream>
#include <vector>

#include "PoscarParser.h"

std::optional<Atoms> PoscarParser::parse()
{
    std::ifstream input(_filename);
    if (!input.is_open()) {
        return std::nullopt;
    }
    
    std::string systemName;
    float scale;
    Cell cell;
    std::vector<std::string> elements;
    std::vector<int> numbers;

    // Read first line as the name of the system
    std::getline(input, systemName);
    // Read second line as the scale
    input >> scale;
    // Read third line as the cell
    input >> cell(0, 0) >> cell(0, 1) >> cell(0, 2);
    input >> cell(1, 0) >> cell(1, 1) >> cell(1, 2);
    input >> cell(2, 0) >> cell(2, 1) >> cell(2, 2);
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Read fourth line as the elements
    std::string line;
    std::getline(input, line);
    std::stringstream ss(line);
    std::string element;
    while (ss >> element) {
        elements.push_back(element);
    }
    // Read fifth line as the numbers
    std::getline(input, line);
    ss = std::stringstream(line);
    int number;
    while (ss >> number) {
        numbers.push_back(number);
    }
    // The number of atoms is the sum of the numbers
    int numAtoms = 0;
    for (int i = 0; i < numbers.size(); i++) {
        numAtoms += numbers[i];
    }
    // Read the rest as the positions
    Eigen::MatrixX3f positions(numAtoms, 3);
    for (int i = 0; i < numAtoms; i++) {
        input >> positions(i, 0) >> positions(i, 1) >> positions(i, 2);
    }

    input.close();

    return std::make_optional<Atoms>(cell, positions, Eigen::ArrayXi::Ones(numAtoms));
}