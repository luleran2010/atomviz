#ifndef WireframeObjects_h
#define WireframeObjects_h

#include <Corrade/Containers/Pointer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Primitives/Grid.h>
#include <Magnum/Shaders/FlatGL.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/Trade/MeshData.h>

#include "FlatShadeObject.h"

using Object3D = Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D>;
using Scene3D  = Magnum::SceneGraph::Scene<Magnum::SceneGraph::MatrixTransformation3D>;

class WireframeObject {
    public:
        explicit WireframeObject(Scene3D* const scene,
            Magnum::SceneGraph::DrawableGroup3D* const drawableGroup) {
            _obj3D.reset(new Object3D{scene});
            _flatShader = Magnum::Shaders::FlatGL3D{};
            _drawableObj.reset(new FlatShadeObject{*_obj3D, _flatShader, Magnum::Color3{0.75f},
                _mesh, drawableGroup});
        }

        WireframeObject& setColor(const Magnum::Color3& color) {
            _drawableObj->setColor(color);
            return *this;
        }
        WireframeObject& transform(const Magnum::Matrix4& matrix) {
            _obj3D->transform(matrix);
            return *this;
        }
        WireframeObject& setTransformation(const Magnum::Matrix4& matrix) {
            _obj3D->setTransformation(matrix);
            return *this;
        }

    protected:
        Magnum::GL::Mesh _mesh{Magnum::NoCreate};
        Magnum::Shaders::FlatGL3D _flatShader{Magnum::NoCreate};
        Corrade::Containers::Pointer<Object3D> _obj3D;
        Corrade::Containers::Pointer<FlatShadeObject> _drawableObj;
};

class WireframeBox: public WireframeObject {
    public:
        explicit WireframeBox(Scene3D* const scene,
            Magnum::SceneGraph::DrawableGroup3D* const drawableGroup):
            WireframeObject{scene, drawableGroup} {
            _mesh = Magnum::MeshTools::compile(Magnum::Primitives::cubeWireframe());
        }
};

class WireframeGrid: public WireframeObject {
    public:
        explicit WireframeGrid(Scene3D* const scene,
            Magnum::SceneGraph::DrawableGroup3D* const drawableGroup):
            WireframeObject{scene, drawableGroup} {
            using namespace Magnum::Math::Literals;

            _mesh = Magnum::MeshTools::compile(Magnum::Primitives::grid3DWireframe({ 20, 20 }));
            _obj3D->scale(Magnum::Vector3(10.0f));
            _obj3D->rotateX(90.0_degf);
    }
};

#endif