#include <Magnum/Math/Color.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/EigenIntegration/Integration.h>

#include "CellDrawable.h"

using namespace Magnum;
using namespace Math::Literals;

CellDrawable::CellDrawable(Object3D &object, Magnum::SceneGraph::DrawableGroup3D& drawables,
    const Cell& cell):
    SceneGraph::Drawable3D{object, &drawables}, _cell{cell}
{
    _shader.reset(new Shaders::FlatGL3D{});
    _mesh = MeshTools::compile(Magnum::Primitives::cubeWireframe());
}

void CellDrawable::draw(const Magnum::Matrix4 &transformation, Magnum::SceneGraph::Camera3D &camera)
{
    Matrix4 cellTransform = Matrix4::from(Matrix3(_cell) / 2, Vector3{0.0f});
    (*_shader)
        .setColor(Color3{0.75f})
        .setTransformationProjectionMatrix(
            camera.projectionMatrix()
            * transformation * cellTransform * Matrix4::translation(Vector3{1.0f})
        )
        .draw(_mesh);
}
