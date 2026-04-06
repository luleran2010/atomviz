add_library(Core STATIC
    Atoms.cpp
    PoscarParser.cpp
)
target_link_libraries(Core PRIVATE
    Eigen3::Eigen)

add_executable(main WIN32 main.cpp ArcBall.cpp)
target_link_libraries(main PRIVATE
    Corrade::Main
    Magnum::Application
    Magnum::DebugTools
    Magnum::GL
    Magnum::Magnum
    Magnum::MeshTools
    Magnum::Primitives
    Magnum::SceneGraph
    Magnum::Shaders)