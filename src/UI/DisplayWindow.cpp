#include "UI/DisplayWindow.h"

void DisplayWindow::draw(bool *p_open)
{
    ImGui::Begin("Display", p_open);

    ImGui::SeparatorText("Atoms");
    if (ImGui::SliderFloat("Atom Scale", &_atomScale, 0.1f, 2.0f)) {
        _atomsDrawable->setAtomScale(_atomScale);
    }

    ImGui::SeparatorText("Bonds");
    if (ImGui::SliderFloat("Bond Radius", &_bondRadius, 0.01f, 0.5f)) {
        _bondsDrawable->setBondRadius(_bondRadius);
    }
    if (ImGui::SliderFloat("Max. Bond Length", &_maxBondLength, 1.0f, 5.0f)) {
        _bondsDrawable->setMaxBondLength(_maxBondLength);
    }
    
    ImGui::End();
}