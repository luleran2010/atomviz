add_library(Core STATIC
    Atoms.cpp
    PoscarParser.cpp
)
target_link_libraries(Core PRIVATE
    Eigen3::Eigen)

add_executable(main WIN32 main.cpp ArcBall.cpp AtomsDrawables.cpp)
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
    Core)
target_compile_definitions(main PRIVATE
    RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/../tests/data/"
)