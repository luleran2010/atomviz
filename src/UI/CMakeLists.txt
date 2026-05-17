add_library(UI STATIC
    MainWindow.cpp
    PropertyWindow.cpp
    DisplayWindow.cpp)
target_link_libraries(UI PRIVATE
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
    ImGuiFileDialog
    Core)