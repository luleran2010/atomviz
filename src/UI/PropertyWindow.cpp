#include "UI/PropertyWindow.h"

void PropertyWindow::draw(bool *p_open)
{
    ImGui::Begin("Properties", p_open);

    ImGui::LabelText("Comment", "%s", _comment.c_str());
    ImGui::Text("%s", "Cell");
    if (ImGui::BeginTable("Cell", 3)) {
        for (int row = 0; row < 3; row++) {
            ImGui::TableNextRow();
            for (int column = 0; column < 3; column++) {
                ImGui::TableSetColumnIndex(column);
                ImGui::Text("%.3f", _cell[row * 3 + column]);
            }
        }
        ImGui::EndTable();
    }

    ImGui::End();
}

void PropertyWindow::setAtoms(Atoms *atoms)
{
    _atoms = atoms;
    _comment = "Simple structure for demonstration";
    for (int i = 0; i < 9; i++) {
        _cell[i] = atoms->cell().data()[i];
    }
}