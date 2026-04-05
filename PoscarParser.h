#ifndef POSCARPARSER_H
#define POSCARPARSER_H

#include <string>
#include <optional>
#include "Atoms.h"

class PoscarParser {
public:
    PoscarParser(const std::string& filename) : _filename(filename) {}

    std::optional<Atoms> parse();

    std::string filename() const { return _filename; }
    void setFilename(const std::string& filename) { _filename = filename; }
private:
    std::string _filename;
};

#endif