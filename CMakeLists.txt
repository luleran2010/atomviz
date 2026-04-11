cmake_minimum_required(VERSION 3.10)

project(AtomViz CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VCPKG_OVERLAY_PORTS "${CMAKE_CURRENT_SOURCE_DIR}/custom-ports")

find_package(Eigen3 CONFIG REQUIRED)
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

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)