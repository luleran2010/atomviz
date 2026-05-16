#include <fstream>
#include <sstream>
#include <vector>

#include "XYZParser.h"
#include "PeriodicTable.h"

std::optional<Atoms> PoscarParser::parse()
{
    std::ifstream input(_filename);
    if (!input.is_open()) {
        return std::nullopt;
    }

    int nAtoms;
    
}