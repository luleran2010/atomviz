add_library(Core STATIC
    Atoms.cpp
    PoscarParser.cpp
)
target_link_libraries(Core PRIVATE
    Eigen3::Eigen
    rapidcsv::rapidcsv)

add_executable(main WIN32 main.cpp ArcBall.cpp AtomsDrawable.cpp CellDrawable.cpp)
target_link_libraries(main PRIVATE
    Corrade::Main
    Magnum::Application
    Magnum::DebugTools
    Magnum::GL
    Magnum::Magnum
    Magnum::MeshTools
    Magnum::Primitives
    Magnum::SceneGraph
    Magnum::Shaders
    Eigen3::Eigen
    MagnumIntegration::Eigen
    Core)
target_compile_definitions(main PRIVATE
    RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../tests/data/"
)
