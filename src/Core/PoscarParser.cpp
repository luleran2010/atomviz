#include <fstream>
#include <sstream>
#include <vector>

#include "PoscarParser.h"
#include "PeriodicTable.h"

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
    std::vector<int> counts;
    bool selective_dynamics = false;
    bool cartesian_coordinates = true;

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
    int count;
    // The number of atoms is the sum of the numbers
    int numAtoms = 0;
    while (ss >> count) {
        counts.push_back(count);
        numAtoms += count;
    }
    Eigen::ArrayXi numbers(numAtoms);
    for (int i = 0, cur = 0; i < counts.size(); i++) {
        numbers.segment(cur, counts[i]) = PeriodicTable::getInstance().getAtomicNumber(elements[i]);
        cur += counts[i];
    }
    // Read the type of coordinates
    input >> line;
    if (line[0] == 'S') {
        selective_dynamics = true;
        input >> line;
    }
    if (line[0] == 'C') cartesian_coordinates = true;
    else cartesian_coordinates = false;
    // Read the rest as the positions
    Eigen::MatrixX3f positions(numAtoms, 3);
    for (int i = 0; i < numAtoms; i++) {
        input >> positions(i, 0) >> positions(i, 1) >> positions(i, 2);
        if (input.peek() != '\n') {
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    input.close();

    if (!cartesian_coordinates) positions = positions * cell;

    return std::make_optional<Atoms>(cell, positions, numbers);
}