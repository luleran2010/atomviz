#ifndef AtomViz_PeriodicTable_h
#define AtomViz_PeriodicTable_h

#include <map>
#include <vector>
#include <string>
#include <rapidcsv.h>

struct Element {
    std::string symbol;
    std::string name;
    float atomicMass;
    float radius;
    unsigned int color;
};

class PeriodicTable {
public:
    PeriodicTable(const PeriodicTable&) = delete;
    PeriodicTable &operator=(const PeriodicTable&) = delete;

    static PeriodicTable &getInstance() {
        static PeriodicTable instance;
        return instance;
    }

    const Element &getElement(int atomicNumber) {
        return elements[atomicNumber - 1];
    }

    const int &getAtomicNumber(const std::string &symbol) {
        return numbers[symbol];
    }
private:
    std::vector<Element> elements;
    std::map<std::string, int> numbers;

    PeriodicTable() {
        loadElements();
        createNumbers();
    }

    void loadElements();
    void createNumbers();
};

#endif