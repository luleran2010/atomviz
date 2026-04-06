#ifndef ATOMSDRAWABLES_H
#define ATOMSDRAWABLES_H

#include <Magnum/GL/Mesh.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/SceneGraph/Object.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/Shaders/PhongGL.h>

#include "Atoms.h"

class AtomsDrawables: public Magnum::SceneGraph::Drawable3D {
public:
    using Object3D = Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D>;
    explicit AtomsDrawables(Object3D& object, Magnum::Shaders::PhongGL& shader,
        Magnum::SceneGraph::DrawableGroup3D& drawables, Atoms& atoms);

    void draw(const Magnum::Matrix4& transformation, Magnum::SceneGraph::Camera3D& camera);
private:
    Magnum::Shaders::PhongGL& _shader;
    Magnum::GL::Mesh _mesh{Magnum::NoCreate};

    Atoms& _atoms;
};

#endif