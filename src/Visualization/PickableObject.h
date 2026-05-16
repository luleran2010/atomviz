#ifndef PickableObject_h
#define PickableObject_h

#include <Magnum/Magnum.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Color.h>
#include <Magnum/SceneGraph/Object.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/Shaders/PhongGL.h>

typedef Magnum::SceneGraph::Scene<Magnum::SceneGraph::MatrixTransformation3D> Scene3D;
typedef Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D> Object3D;

class PickableObject: public Object3D, Magnum::SceneGraph::Drawable3D {
public:
    explicit PickableObject(unsigned int id, Magnum::Shaders::PhongGL& shader,
        const Magnum::Color3 &color, Magnum::GL::Mesh& mesh, Object3D& parent,
        Magnum::SceneGraph::DrawableGroup3D& drawbles):
        Object3D{&parent}, Magnum::SceneGraph::Drawable3D{*this, &drawbles},
        _id{id}, _selected{false}, _shader{shader}, _color{color}, _mesh(mesh) {}

private:
    virtual void draw(const Magnum::Matrix4& transformationMatrix,
        Magnum::SceneGraph::Camera3D& camera) {
        _shader.setTransformationMatrix(transformationMatrix)
            .setNormalMatrix(transformationMatrix.normalMatrix())
            .setProjectionMatrix(camera.projectionMatrix())
            .setAmbientColor(_selected ? _color*0.3f : Magnum::Color3{})
            .setDiffuseColor(_color*(_selected ? 2.0f : 1.0f))
            /* relative to the camera */
            .setLightPositions({{13.0f, 2.0f, 5.0f, 0.0f}})
            .setObjectId(_id)
            .draw(_mesh);
    }

    unsigned int _id;
    bool _selected;
    Magnum::Shaders::PhongGL& _shader;
    Magnum::Color3 _color;
    Magnum::GL::Mesh& _mesh;
};

#endif