add_subdirectory(Core)

add_subdirectory(Visualization)

add_subdirectory(UI)

add_executable(main WIN32 main.cpp)
target_link_libraries(main PRIVATE
    Corrade::Main
    Magnum::Application
    Magnum::DebugTools
    MagnumIntegration::ImGui
    Core
    Visualization
    UI)