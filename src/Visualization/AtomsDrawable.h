#ifndef AtomViz_AtomsDrawable_h
#define AtomViz_AtomsDrawable_h

#include <Corrade/Containers/Pointer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/SceneGraph/Object.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/Shaders/PhongGL.h>

#include "Atoms.h"

class AtomsDrawable: public Magnum::SceneGraph::Drawable3D
{
public:
    using Object3D = Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D>;
    explicit AtomsDrawable(Object3D& object, Magnum::SceneGraph::DrawableGroup3D& drawables,
        Atoms& atoms);

    void draw(const Magnum::Matrix4& transformation, Magnum::SceneGraph::Camera3D& camera) override;

    float atomScale() const { return _atomScale; }
    void setAtomScale(float scale) { _atomScale = scale; }
private:
    Corrade::Containers::Pointer<Magnum::Shaders::PhongGL> _shader;
    Magnum::GL::Mesh _mesh{Magnum::NoCreate};

    Atoms& _atoms;

    float _atomScale = 1.0f;
};

#endif