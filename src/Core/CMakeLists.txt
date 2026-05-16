add_library(Core STATIC
    Atoms.cpp
    PoscarParser.cpp
    PeriodicTable.cpp
)
target_link_libraries(Core PRIVATE
    Eigen3::Eigen
    rapidcsv::rapidcsv)