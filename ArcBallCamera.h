#ifndef AtomViz_ArcBallCamera_h
#define AtomViz_ArcBallCamera_h

#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/AbstractTranslationRotation3D.h>
#include <Magnum/SceneGraph/Object.h>
#include <Magnum/SceneGraph/Scene.h>

#include "ArcBall.h"

// Arcball camera implementatin integrated into the SceneGraph
class ArcBallCamera: public ArcBall {
public:
    template<class Transformation> ArcBallCamera(
        Magnum::SceneGraph::Scene<Transformation>& scene,
        const Magnum::Vector3& cameraPosition, const Magnum::Vector3& viewCenter,
        const Magnum::Vector3& upDir, Magnum::Deg fov, const Magnum::Vector2i& windowSize,
        const Magnum::Vector2i& viewportSize):
        ArcBall{cameraPosition, viewCenter, upDir, fov, windowSize}
    {
        // Create a camera object of a concrete type
        auto* cameraObject = new Magnum::SceneGraph::Object<Transformation>{&scene};
        _camera = new Magnum::SceneGraph::Camera3D{*cameraObject};
        (*_camera).setAspectRatioPolicy(Magnum::SceneGraph::AspectRatioPolicy::Extend)
            .setProjectionMatrix(Magnum::Matrix4::perspectiveProjection(
                fov, Magnum::Vector2{windowSize}.aspectRatio(), 0.01f, 100.0f))
            .setViewport(viewportSize);

        // Save the abstract transformation interface and initialze the camera position through that
        _cameraObject = cameraObject;
        (*_cameraObject).rotate(this->transformation().rotation())
                .translate(this->transformation().translation());
    }

    // Update screen and viewport size after the window has been resize
    void reshape(const Magnum::Vector2i& windowSize, const Magnum::Vector2i& viewportSize) {
        _windowSize = windowSize;
        _camera->setViewport(viewportSize);
    }

    // Update the SceneGraph camera if arcball has been changed
    bool update() {
        // Call the intermal update
        if (!updateTransformation()) {
            return false;
        }

        (*_cameraObject).resetTransformation()
            .rotate(transformation().rotation())
            .translate(transformation().translation());
        return true;
    }

    // Draw objects using the internal scenegraph camera
    void draw(Magnum::SceneGraph::DrawableGroup3D& drawables) {
        _camera->draw(drawables);
    }

    // Accessor to the raw camera object
    Magnum::SceneGraph::Camera3D& camera() const {
        return *_camera;
    }

private:
    Magnum::SceneGraph::AbstractTranslationRotation3D* _cameraObject{};
    Magnum::SceneGraph::Camera3D* _camera;
};

#endif