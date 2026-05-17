#ifndef AtomViz_MainWindow_h
#define AtomViz_MainWindow_h

#include <string>
#include <Magnum/ImGuiIntegration/Context.h>

#include "UI/ImGuiWindow.h"

class MainWindow: public ImGuiWindow {
public:
    MainWindow(): ImGuiWindow() {}
    ~MainWindow() {}
    void draw(bool *p_open) override;

    std::string filename() const { return _filename;}

private:
    std::string _filename = "";
};

#endif