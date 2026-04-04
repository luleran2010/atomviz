#ifndef AtomViz_ArcBall_h
#define AtomViz_ArcBall_h

#include <Magnum/Magnum.h>
#include <Magnum/Math/Functions.h>
#include <Magnum/Math/DualQuaternion.h>
#include <Magnum/Math/Vector2.h>
#include <Magnum/Math/Vector3.h>

class ArcBall {
public:
    ArcBall(const Magnum::Vector3& cameraPosition, const Magnum::Vector3& viewCenter,
        const Magnum::Vector3& upDir, Magnum::Deg fov, const Magnum::Vector2i& windowSize);
    
    // Set the camera view parameters: eye position, view center, up direction
    void setViewParameters(const Magnum::Vector3& eye, const Magnum::Vector3& viewCenter,
        const Magnum::Vector3& upDir);

    // Reset the camera to its initial position, view center, and up dir
    void reset();

    // Update screen size after the window has been resized
    void reshape(const Magnum::Vector2i& windowSize) {
        _windowSize = windowSize;
    }

    // Update any unfinished transformation due to lagging, return true if the camera matrices have
    // changed
    bool updateTransformation();

    // Get/Set the amount of lagging such that the camera will (slowly) smoothly navigate. Lagging
    // must be in [0, 1)
    float lagging() const {
        return _lagging;
    }
    void setLagging(float lagging);

    // Initialize the first (screen) pointer position for camera transformation. This should be
    // called in pointer pressed event.
    void initTransformation(const Magnum::Vector2& pointerPosition);

    // Rotate the camera from the previous (screen) pointer position to the current (screen)
    // position
    void rotate(const Magnum::Vector2& pointerPosition);

    // Translate the camera from the preview (screen) pointer position to the current (screen)
    // position
    void translate(const Magnum::Vector2& pointerPosition);

    // Translate the camera by the delta amount of (NDC) pointer position. Note that NDC position
    // must be in [-1, -1] to [1, 1].
    void translateDelta(const Magnum::Vector2& translationNdc);

    // Zoom the camera (positive delta = zoom in, negative = zoom out)
    void zoom(float delta);

    Magnum::Deg fov() const {
        return _fov;
    }

    // Get the camera's view transformation as a qual quaternion
    const Magnum::DualQuaternion& view() const {
        return _view;
    }

    // Get the camera's view transformation as a matrix
    Magnum::Matrix4 viewMatrix() const {
        return _view.toMatrix();
    }

    // Get the camera's inverse view matrix (which also produces tarnsformation of the camera)
    Magnum::Matrix4 inverseViewMatrix() const {
        return _inverseView.toMatrix();
    }

    // Get the camera's transformation as a dual quaternion
    const Magnum::DualQuaternion& transformation() const {
        return _inverseView;
    }

    // Get the camera's transformation matrix
    Magnum::Matrix4 transformationMatrix() const {
        return _inverseView.toMatrix();
    }

    // Return the distance from the camera position to the center view
    float viewDistance() const {
        return Magnum::Math::abs(_targetZooming);
    }

protected:
    // Update the camera transformations
    void updateInternalTransformations();

    // Transform from screen coordinate to NDC -- normalized device coordinate. The top-left of the
    // screen corresponds to [-1, 1] NDC, and the bottom right is [1, -1] NDC.
    Magnum::Vector2 screenCoordToNdc(const Magnum::Vector2& pointerPosition) const;

    Magnum::Deg _fov;
    Magnum::Vector2i _windowSize;

    Magnum::Vector2 _prevPointerPositionNdc;
    float _lagging{};

    Magnum::Vector3 _targetPosition, _currentPosition, _positionT0;
    Magnum::Quaternion _targetQRotation, _currentQRotation, _qRotationT0;
    float _targetZooming, _currentZooming, _zoomingT0;
    Magnum::DualQuaternion _view, _inverseView;
};

#endif