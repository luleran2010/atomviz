add_library(Visualization STATIC
    ArcBall.cpp
    AtomsDrawable.cpp
    BondsDrawable.cpp
    CellDrawable.cpp
    AxisDrawable.cpp)
target_link_libraries(Visualization PRIVATE
    Magnum::DebugTools
    Magnum::GL
    Magnum::Magnum
    Magnum::MeshTools
    Magnum::Primitives
    Magnum::SceneGraph
    Magnum::Shaders
    Eigen3::Eigen
    MagnumIntegration::Eigen
    MagnumIntegration::ImGui
    Core)