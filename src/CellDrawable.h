#ifndef AtomViz_CellDrawable_h
#define AtomViz_CellDrawable_h

#include <Corrade/Containers/Pointer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/SceneGraph/Object.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Shaders/FlatGL.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>

#include "typedefs.h"

class CellDrawable: public Magnum::SceneGraph::Drawable3D {
public:
    using Object3D = Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D>;
    explicit CellDrawable(Object3D& object, Magnum::SceneGraph::DrawableGroup3D& drawables,
        const Cell& cell);

    void draw(const Magnum::Matrix4& transformation, Magnum::SceneGraph::Camera3D& camera);
private:
    Corrade::Containers::Pointer<Magnum::Shaders::FlatGL3D> _shader;
    Magnum::GL::Mesh _mesh{Magnum::NoCreate};

    Cell _cell;
};

#endif