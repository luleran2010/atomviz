#include <Magnum/Primitives/Icosphere.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/EigenIntegration/Integration.h>

#include "AtomsDrawables.h"

using namespace Magnum;
using namespace Math::Literals;

AtomsDrawables::AtomsDrawables(Object3D& object, Shaders::PhongGL &shader,
    SceneGraph::DrawableGroup3D& drawables, Atoms& atoms):
    SceneGraph::Drawable3D{object, &drawables}, _shader(shader), _atoms(atoms)
{
    const Trade::MeshData sphere = Primitives::icosphereSolid(3);
    _mesh = MeshTools::compile(sphere);
}

void AtomsDrawables::draw(const Matrix4 &transformation, SceneGraph::Camera3D &camera)
{
    for (size_t i = 0; i < _atoms.size(); i++) {
        Matrix4 atomMatrix = Matrix4::translation(Vector3{_atoms[i].position()})
            + Matrix4::scaling(Vector3{1.0f});
        _shader
            .setTransformationMatrix(transformation * atomMatrix)
            .setProjectionMatrix(camera.projectionMatrix())
            .draw(_mesh);
    }
}
