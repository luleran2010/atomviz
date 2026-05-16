#ifndef AtomViz_AxisDrawable_h
#define AtomViz_AxisDrawable_h

#include <Corrade/Containers/Pointer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/SceneGraph/Object.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/Shaders/VertexColorGL.h>

class AxisDrawable: public Magnum::SceneGraph::Drawable3D
{
public:
    using Object3D = Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D>;
    explicit AxisDrawable(Object3D &object, Magnum::SceneGraph::DrawableGroup3D &drawables);
    
    void draw(const Magnum::Matrix4 &transformation, Magnum::SceneGraph::Camera3D &camera);
private:
    Corrade::Containers::Pointer<Magnum::Shaders::VertexColorGL3D> _shader;
    Magnum::GL::Mesh _mesh{Magnum::NoCreate};
};

#endif