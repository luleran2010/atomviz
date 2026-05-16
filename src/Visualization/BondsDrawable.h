#ifndef AtomViz_BondsDrawable_h
#define AtomViz_BondsDrawable_h

#include <Corrade/Containers/Pointer.h>
#include <Corrade/Containers/Array.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/SceneGraph/Object.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/Shaders/PhongGL.h>

#include <Eigen/Dense>
#include <Magnum/EigenIntegration/Integration.h>

#include "Atoms.h"

class BondsDrawable: public Magnum::SceneGraph::Drawable3D
{
public:
    using Object3D = Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D>;
    explicit BondsDrawable(Object3D &object, Magnum::SceneGraph::DrawableGroup3D &drawables,
        Atoms &atoms, float maxBondLength = 3.0f);

    void draw(const Magnum::Matrix4 &transformation, Magnum::SceneGraph::Camera3D &camera) override;

    void setBondRadius(float bondRadius) {
        _bondRadius = bondRadius;
        calculateBondTransformations();
    }

    float maxBondLength() const { return _maxBondLength; }
    void setMaxBondLength(float maxBondLength) {
        _maxBondLength = maxBondLength;
        calculateBondTransformations();
    }
private:
    void calculateBondLengths();
    void calculateBondTransformations();

    Corrade::Containers::Pointer<Magnum::Shaders::PhongGL> _shader;
    Magnum::GL::Mesh _mesh{Magnum::NoCreate};

    Atoms &_atoms;

    float _bondRadius = 0.2f;
    float _maxBondLength;
    Eigen::ArrayXXf _bondLengths;
    Corrade::Containers::Array<Magnum::Matrix4> _bondTransformations;
};

#endif