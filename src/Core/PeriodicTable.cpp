#include "PeriodicTable.h"

void PeriodicTable::loadElements()
{
    rapidcsv::Document doc(
        RESOURCE_DIR + std::string("ptable.csv"),
        rapidcsv::LabelParams(),
        rapidcsv::SeparatorParams(),
        rapidcsv::ConverterParams(true)
    );

    auto colorConverter = [](const std::string& str, unsigned int& pVal) {
        pVal = str.empty() ? 0xffffff : static_cast<unsigned int>(std::stoul(str, nullptr, 16));
    };

    for (int i = 0; i < doc.GetRowCount(); i++) {
        Element element;
        element.symbol = doc.GetCell<std::string>("Symbol", i);
        element.name = doc.GetCell<std::string>("Name", i);
        element.atomicMass = doc.GetCell<float>("AtomicMass", i);
        element.radius = doc.GetCell<float>("AtomicRadius", i) * 1e-2f;
        element.color = doc.GetCell<unsigned int>("CPKHexColor", i, colorConverter);
        elements.push_back(element);
    }
}

void PeriodicTable::createNumbers()
{
    for (int i = 0; i < elements.size(); i++) {
        numbers[elements[i].symbol] = i + 1;
    }
}
