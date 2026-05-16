#ifndef AtomViz_ImGuiWindow_h
#define AtomViz_ImGuiWindow_h

#include <Magnum/ImGuiIntegration/Context.hpp>

class ImGuiWindow {
public:
    ImGuiWindow() {}
    virtual ~ImGuiWindow() {}

    virtual void draw(bool *p_open) = 0;
};

#endif