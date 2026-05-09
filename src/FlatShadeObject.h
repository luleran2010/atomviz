#ifndef FlatShadeObject_h
#define FlatShadeObject_h

#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Shaders/FlatGL.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>

using Object3D = Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D>;

class FlatShadeObject: public Magnum::SceneGraph::Drawable3D {
public:
    explicit FlatShadeObject(Object3D& object, Magnum::Shaders::FlatGL3D& shader,
        const Magnum::Color3& color, Magnum::GL::Mesh& mesh,
        Magnum::SceneGraph::DrawableGroup3D* const drawables):
        Magnum::SceneGraph::Drawable3D{object, drawables}, _shader(shader), _color(color),
        _mesh(mesh) {}

    void draw(const Magnum::Matrix4& transformation, Magnum::SceneGraph::Camera3D& camera) override {
        _shader
            .setColor(_color)
            .setTransformationProjectionMatrix(camera.projectionMatrix() * transformation)
            .draw(_mesh);
    }

    FlatShadeObject& setColor(const Magnum::Color3& color) { _color = color; return *this; }

private:
    Magnum::Shaders::FlatGL3D& _shader;
    Magnum::Color3 _color;
    Magnum::GL::Mesh& _mesh;
};


#endif