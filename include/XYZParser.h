#ifndef AtomViz_XYZParser_h
#define AtomViz_XYZParser_h

#include <string>
#include <optional>
#include "Atoms.h"

class XYZParser {
public:
    XYZParser(const std::string& filename) : _filename(filename) {}

    std::optional<Atoms> parse();

    std::string filename() const { return _filename; }
    void setFilename(const std::string& filename) { _filename = filename; }
private:
    std::string _filename;
};

#endif