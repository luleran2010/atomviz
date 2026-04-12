cmake_minimum_required(VERSION 3.10)

set(VCPKG_OVERLAY_PORTS "${CMAKE_CURRENT_LIST_DIR}/custom-ports")

project(AtomViz CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
  add_compile_options(/utf-8)
endif()

# set(VCPKG_OVERLAY_PORTS "${CMAKE_CURRENT_SOURCE_DIR}/custom-ports")

# Corrade
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/corrade/modules/" ${CMAKE_MODULE_PATH})
add_subdirectory(corrade EXCLUDE_FROM_ALL) # so only things you use are built

# Magnum
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/magnum/modules/" ${CMAKE_MODULE_PATH})
set(MAGNUM_WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)
add_subdirectory(magnum EXCLUDE_FROM_ALL)

# Magnum Integration
set(MAGNUM_WITH_EIGENINTEGRATION ON CACHE BOOL "" FORCE)
set(MAGNUM_WITH_IMGUIINTEGRATION ON CACHE BOOL "" FORCE)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/magnum-integration/modules/" ${CMAKE_MODULE_PATH})
add_subdirectory(magnum-integration EXCLUDE_FROM_ALL)

find_package(imgui CONFIG REQUIRED)
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
