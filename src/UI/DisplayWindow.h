#ifndef AtomViz_DisplayWindow_h
#define AtomViz_DisplayWindow_h

#include <string>
#include <Magnum/ImGuiIntegration/Context.h>

#include "UI/ImGuiWindow.h"
#include "Visualization/AtomsDrawable.h"
#include "Visualization/BondsDrawable.h"

class DisplayWindow: public ImGuiWindow
{
public:
    DisplayWindow(): ImGuiWindow(), _atomsDrawable(nullptr), _bondsDrawable(nullptr) {}

    virtual ~DisplayWindow() {}

    virtual void draw(bool *p_open) override;

    AtomsDrawable *atomsDrawable() { return _atomsDrawable; }
    void setAtomsDrawable(AtomsDrawable *atomsDrawable) { _atomsDrawable = atomsDrawable; }

    BondsDrawable *bondsDrawable() { return _bondsDrawable; }
    void setBondsDrawable(BondsDrawable *bondsDrawable) { _bondsDrawable = bondsDrawable; }

    float atomScale() const { return _atomScale; }
    float bondRadius() const { return _bondRadius; }
private:
    float _atomScale = 0.8f;
    float _bondRadius = 0.2f;
    float _maxBondLength = 3.0f;

    AtomsDrawable *_atomsDrawable;
    BondsDrawable *_bondsDrawable;
};

#endif