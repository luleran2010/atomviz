#include <Magnum/Primitives/Icosphere.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/Math/Color.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/EigenIntegration/Integration.h>

#include "AtomsDrawable.h"

using namespace Magnum;
using namespace Math::Literals;

AtomsDrawable::AtomsDrawable(Object3D& object,
    SceneGraph::DrawableGroup3D& drawables, Atoms& atoms):
    SceneGraph::Drawable3D{object, &drawables}, _atoms(atoms)
{
    _shader.reset(new Shaders::PhongGL{Shaders::PhongGL::Configuration{}.setLightCount(2)});
    const Trade::MeshData sphere = Primitives::icosphereSolid(3);
    _mesh = MeshTools::compile(sphere);
}

void AtomsDrawable::draw(const Matrix4 &transformation, SceneGraph::Camera3D &camera)
{
    for (size_t i = 0; i < _atoms.size(); i++) {
        Matrix4 atomMatrix = Matrix4::translation(Vector3{_atoms[i].position()})
            * Matrix4::scaling(Vector3{1.0f});
        (*_shader)
            .setLightPositions({
                {10.0f, 10.0f, 10.0f, 0.0f},
                {-5.0f, -5.0f, 10.0f, 0.0f}
            })
            .setLightColors({Color3{1.0f}, Color3{0.3f}})
            .setTransformationMatrix(transformation * atomMatrix)
            .setProjectionMatrix(camera.projectionMatrix())
            .draw(_mesh);
    }
}
