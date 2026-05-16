#include "Atoms.h"

Atoms::Atoms(const Cell &cell, const Eigen::MatrixX3f &positions, Eigen::ArrayXi numbers):
    _cell{cell}, _positions{positions}, _numbers{numbers}
{
    _size = positions.rows();

    _forces = Eigen::MatrixX3f::Zero(_size, 3);
    _velocities = Eigen::MatrixX3f::Zero(_size, 3);
    _masses = Eigen::ArrayXf::Zero(_size);
    _charges = Eigen::ArrayXf::Zero(_size);

}

Atoms::Atoms(const Cell &cell, const std::vector<Atom> &atoms):
    _cell{cell}
{
    _size = atoms.size();
    _positions = Eigen::MatrixX3f::Zero(_size, 3);
    _forces = Eigen::MatrixX3f::Zero(_size, 3);
    _velocities = Eigen::MatrixX3f::Zero(_size, 3);
    _numbers = Eigen::ArrayXi::Zero(_size);
    _masses = Eigen::ArrayXf::Zero(_size);
    _charges = Eigen::ArrayXf::Zero(_size);

    for (size_t i = 0; i < _size; i++) {
        _positions.row(i) = atoms[i].position();
        _numbers[i] = atoms[i].number();
        _masses[i] = atoms[i].mass();
        _charges[i] = atoms[i].charge();
    }
}

void Atoms::setCell(const Cell &cell, bool wrap)
{
    _cell = cell;
    if (wrap) wrapPositions();
}