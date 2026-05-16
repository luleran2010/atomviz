#include <cmath>
#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/GrowableArray.h>
#include <Magnum/Primitives/Cylinder.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/Math/Quaternion.h>
#include <Magnum/Math/Color.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/EigenIntegration/Integration.h>

#include "BondsDrawable.h"

using namespace Magnum;
using namespace Math::Literals;

BondsDrawable::BondsDrawable(Object3D &object,
    Magnum::SceneGraph::DrawableGroup3D &drawables, Atoms &atoms, float maxBondLength):
    SceneGraph::Drawable3D{object, &drawables}, _atoms(atoms), _maxBondLength(maxBondLength)
{
    _shader.reset(new Shaders::PhongGL{Shaders::PhongGL::Configuration{}.setLightCount(2)});
    const Trade::MeshData cylinder = Primitives::cylinderSolid(5, 10, 0.5f);
    _mesh = MeshTools::compile(cylinder);

    calculateBondLengths();
    calculateBondTransformations();
}

void BondsDrawable::draw(const Magnum::Matrix4 & transformation, Magnum::SceneGraph::Camera3D & camera)
{
    for (size_t i = 0; i < _bondTransformations.size(); i++) {
        (*_shader)
            .setLightPositions({
                {10.0f, 10.0f, 10.0f, 0.0f},
                {-10.0f, -10.0f, -10.0f, 0.0f}
            })
            .setLightColors({Color3::fromLinearRgbInt(0xffffff), Color3::fromLinearRgbInt(0xffffff)})
            .setTransformationMatrix(transformation * _bondTransformations[i])
            .setProjectionMatrix(camera.projectionMatrix())
            .draw(_mesh);
    }
}

void BondsDrawable::calculateBondLengths()
{
    _bondLengths = Eigen::ArrayXXf::Zero(_atoms.size(), _atoms.size());
    for (size_t i = 0; i < _atoms.size(); i++) {
        for (size_t j = i + 1; j < _atoms.size(); j++) {
            _bondLengths(i, j) = (_atoms.positions().row(i) - _atoms.positions().row(j)).norm();
            if (_bondLengths(i, j) < _maxBondLength) {
            }
        }
    }
}

void BondsDrawable::calculateBondTransformations()
{
    int count = (_bondLengths - _maxBondLength).cwiseLess(0.0f).count() - _atoms.size() * (_atoms.size() + 1) / 2;
    Corrade::Containers::arrayReserve(_bondTransformations, count);
    Corrade::Containers::arrayResize(_bondTransformations, count);

    int index = 0;
    for (size_t i = 0; i < _atoms.size(); i++) {
        for (size_t j = i + 1; j < _atoms.size(); j++) {
            if (_bondLengths(i, j) < _maxBondLength) {
                Eigen::Vector3f direction = (_atoms.positions().row(j) - _atoms.positions().row(i)).normalized();
                Eigen::Vector3f translation = (_atoms.positions().row(i) + _atoms.positions().row(j)) / 2;
                Matrix3 rotation = Quaternion::rotation(Vector3{0.0f, 1.0f, 0.0f}, Vector3{direction}).toMatrix();
                Matrix4 scaling = Matrix4::scaling(Vector3{_bondRadius, _bondLengths(i, j), _bondRadius});
                Magnum::Matrix4 bondMatrix = Matrix4::from(rotation, Vector3{translation}) * scaling;
                _bondTransformations[index] = bondMatrix;
                index += 1;
            }
        }
    }
}
