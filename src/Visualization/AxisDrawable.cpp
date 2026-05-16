#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Primitives/Axis.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/Math/Color.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/EigenIntegration/Integration.h>

#include "AxisDrawable.h"

using namespace Magnum;
using namespace Math::Literals;

AxisDrawable::AxisDrawable(Object3D &object,
    Magnum::SceneGraph::DrawableGroup3D &drawables):
    SceneGraph::Drawable3D{object, &drawables}
{
    _shader.reset(new Shaders::VertexColorGL3D{});
    const Trade::MeshData axis = Primitives::axis3D();
    _mesh = MeshTools::compile(axis);
}

void AxisDrawable::draw(const Magnum::Matrix4 &transformation, Magnum::SceneGraph::Camera3D &camera)
{
    Range2Di originalViewport = GL::defaultFramebuffer.viewport();
    GL::defaultFramebuffer.setViewport(Range2Di::fromSize({0, 0}, {200, 200}));

    Matrix3 rotation = transformation.rotationNormalized();
    Matrix4 axisTransformation = Matrix4::from(rotation, Vector3{0.0f}) * Matrix4::scaling(Vector3{1.0f});
    (*_shader)
        .setTransformationProjectionMatrix(
            axisTransformation
        )
        .draw(_mesh);

    GL::defaultFramebuffer.setViewport(originalViewport);
}
