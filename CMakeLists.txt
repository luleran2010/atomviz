cmake_minimum_required(VERSION 3.10)

project(AtomViz CXX)

find_package(Corrade REQUIRED Main)
find_package(Magnum REQUIRED
    DebugTools
    GL
    MeshTools
    Primitives
    SceneGraph
    Shaders
    Sdl2Application)

find_package(MagnumIntegration REQUIRED Eigen ImGui)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

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