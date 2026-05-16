#ifndef AtomViz_PropertyWindow_h
#define AtomViz_PropertyWindow_h

#include <string>
#include <Eigen/Dense>
#include <Magnum/ImGuiIntegration/Context.hpp>

#include "Atoms.h"
#include "UI/ImGuiWindow.h"

class PropertyWindow: public ImGuiWindow
{
public:
    PropertyWindow(): ImGuiWindow(), _atoms(nullptr), _comment(""), _cell{0,0,0,0,0,0,0,0,0} {}
    ~PropertyWindow() {}

    void draw(bool *p_open) override;
    
    Atoms *atoms() { return _atoms; }
    void setAtoms(Atoms *atoms);

    std::string comment() { return _comment; }
    float *cell() { return _cell; }
private:
    Atoms *_atoms;

    std::string _comment;
    float _cell[9];
};

#endif