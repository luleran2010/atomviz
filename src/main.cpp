#include <Corrade/Containers/Optional.h>
#include <Corrade/Containers/Pointer.h>
#include <Magnum/ImageView.h>
#include <Magnum/PixelFormat.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/TextureFormat.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/Math/Time.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Object.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/EigenIntegration/Integration.h>
#include <Magnum/ImGuiIntegration/Context.hpp>

#include "Visualization/ArcBall.h"
#include "Visualization/ArcBallCamera.h"

#include "Atoms.h"
#include "PoscarParser.h"

#include "Visualization/AxisDrawable.h"
#include "Visualization/AtomsDrawable.h"
#include "Visualization/BondsDrawable.h"
#include "Visualization/CellDrawable.h"

#include "UI/PropertyWindow.h"
#include "UI/DisplayWindow.h"

using namespace Magnum;

using Object3D = SceneGraph::Object<SceneGraph::MatrixTransformation3D>;

using namespace Math::Literals;

class AtomViz: public Platform::Application {
public:
    explicit AtomViz(const Arguments& arguments);

private:
    void drawEvent() override;
    void viewportEvent(ViewportEvent& event) override;
    void keyPressEvent(KeyEvent& event) override;
    void pointerPressEvent(PointerEvent& event) override;
    void pointerReleaseEvent(PointerEvent& event) override;
    void pointerMoveEvent(PointerMoveEvent& event) override;
    void scrollEvent(ScrollEvent& event) override;
    void textInputEvent(TextInputEvent& event) override;

    SceneGraph::Scene<SceneGraph::MatrixTransformation3D> _scene;
    Containers::Optional<ArcBallCamera> _arcballCamera;

    SceneGraph::DrawableGroup3D _drawables;
    Corrade::Containers::Pointer<AxisDrawable> _axisDrawable;
    Corrade::Containers::Pointer<AtomsDrawable> _atomsDrawable;
    Corrade::Containers::Pointer<BondsDrawable> _bondsDrawable;
    Corrade::Containers::Pointer<CellDrawable> _cellDrawable;
    GL::Mesh _mesh{NoCreate};

    ImGuiIntegration::Context _imgui{Magnum::NoCreate};

    bool _showPropertyWindow = true;
    PropertyWindow _propertyWindow;
    bool _showDisplayWindow = true;
    DisplayWindow _displayWindow;

    Atoms _atoms;
};

AtomViz::AtomViz(const Arguments& arguments):
    Platform::Application{arguments, NoCreate}
{
    // Setup window
    const Vector2 dpiScaling = this->dpiScaling({});
    Configuration conf;
    conf.setTitle("AtomViz")
        .setSize(conf.size(), dpiScaling)
        .setWindowFlags(Configuration::WindowFlag::Resizable);
    GLConfiguration glConf;
    glConf.setSampleCount(dpiScaling.max() < 2.0f ? 8 : 2);
    if (!tryCreate(conf, glConf)) {
        create(conf, glConf.setSampleCount(0));
    }
    
    {
        ImGui::CreateContext();

        _imgui = ImGuiIntegration::Context(*ImGui::GetCurrentContext(),
            Vector2{windowSize()}/dpiScaling, windowSize(), framebufferSize());

        GL::Renderer::setBlendEquation(GL::Renderer::BlendEquation::Add,
            GL::Renderer::BlendEquation::Add);
        GL::Renderer::setBlendFunction(GL::Renderer::BlendFunction::SourceAlpha,
            GL::Renderer::BlendFunction::OneMinusSourceAlpha);
    }

    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);

    Debug{} << "The window has been setup";

    // Setup objects
    {
        auto axisObj = new Object3D{&_scene};
        _axisDrawable.reset(new AxisDrawable{*axisObj, _drawables});

        auto atomsObj = new Object3D{&_scene};
        auto bondsObj = new Object3D{&_scene};
        auto cellObj = new Object3D{&_scene};
        // PoscarParser parser(RESOURCE_DIR + std::string("Zn.vasp"));
        PoscarParser parser(RESOURCE_DIR + std::string("ZrInCuS4.poscar"));
        if (auto atoms = parser.parse()) {
            Debug{} << "The structure file has been successfully parsed";
            _atoms = *atoms;
            _atomsDrawable.reset(new AtomsDrawable{*atomsObj, _drawables, _atoms});
            _bondsDrawable.reset(new BondsDrawable{*bondsObj, _drawables, _atoms});
            _cellDrawable.reset(new CellDrawable{*cellObj, _drawables, _atoms.cell()});
        } else {
            Debug{} << "The structure file could not be parsed";
            // Exit the application
            exit();
        }
    }

    _propertyWindow.setAtoms(&_atoms);
    _displayWindow.setAtomsDrawable(_atomsDrawable.get());
    _displayWindow.setBondsDrawable(_bondsDrawable.get());

    // Set up the camera
    {
        const Vector3 eye = Vector3::zAxis(-10.0f);
        const Vector3 center(Eigen::Vector3f(_atoms.cell().colwise().sum().transpose() / 2.0f));
        const Vector3 up = Vector3::yAxis();
        _arcballCamera.emplace(_scene, eye, center, up, 45.0_degf, windowSize(), framebufferSize());

        Debug{} << "The camera has been setup";
    }

    // Loop at 60 Hz max
    setSwapInterval(1);
    setMinimalLoopPeriod(16.0_msec);
}

void AtomViz::drawEvent() {
    GL::defaultFramebuffer.clear(
        GL::FramebufferClear::Color|GL::FramebufferClear::Depth);

    // Call arcball update in every frame. This will do nothing if the camera has not been changed.
    // Otherwise, camera transformation will be propagated into the camera objects.
    // bool camChanged = _arcballCamera->update();
    _arcballCamera->update();
    _arcballCamera->draw(_drawables);
    // swapBuffers();

    // if (camChanged) redraw();

    Debug{} << "The camera has been updated in the draw event";

    _imgui.newFrame();

    if (ImGui::GetIO().WantTextInput && !isTextInputActive()) startTextInput();
    else if (!ImGui::GetIO().WantTextInput && isTextInputActive()) stopTextInput();

    _propertyWindow.draw(&_showPropertyWindow);
    _displayWindow.draw(&_showDisplayWindow);

    _imgui.updateApplicationCursor(*this);

    GL::Renderer::enable(GL::Renderer::Feature::Blending);
    GL::Renderer::enable(GL::Renderer::Feature::ScissorTest);
    GL::Renderer::disable(GL::Renderer::Feature::FaceCulling);
    GL::Renderer::disable(GL::Renderer::Feature::DepthTest);

    _imgui.drawFrame();

    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);
    GL::Renderer::disable(GL::Renderer::Feature::Blending);
    GL::Renderer::disable(GL::Renderer::Feature::ScissorTest);

    swapBuffers();
    redraw();
}

void AtomViz::viewportEvent(ViewportEvent& event) {
    GL::defaultFramebuffer.setViewport({{}, event.framebufferSize()});

    _imgui.relayout(Vector2{event.windowSize()}/event.dpiScaling(),
        event.windowSize(), event.framebufferSize());
        
    _arcballCamera->reshape(event.windowSize(), event.framebufferSize());


    Debug{} << "The viewport has been updated in the viewport event";
}

void AtomViz::keyPressEvent(KeyEvent& event) {
    if (_imgui.handleKeyPressEvent(event)) {
        // Prevent ImGui from capturing the key
        event.setAccepted();
        return;
    }
    event.setAccepted();
}

void AtomViz::pointerPressEvent(PointerEvent& event) {
    if (_imgui.handlePointerPressEvent(event)) {
        // Prevent ImGui from capturing the pointer
        event.setAccepted();
        return;
    }

    if (!event.isPrimary() || !(event.pointer() & (Pointer::MouseLeft|Pointer::Finger))) return;

    // Enable mouse capture so the mouse can drag outside of the window
    SDL_CaptureMouse(SDL_TRUE);

    _arcballCamera->initTransformation(event.position());

    event.setAccepted();
    redraw(); // Camera has changed, redraw!
}

void AtomViz::pointerReleaseEvent(PointerEvent& event) {
    if (_imgui.handlePointerReleaseEvent(event)) {
        // Prevent ImGui from capturing the pointer
        event.setAccepted();
        return;
    }

    if (!event.isPrimary() || !(event.pointer() & (Pointer::MouseLeft|Pointer::Finger))) return;

    // Disable mouse capture agin

    SDL_CaptureMouse(SDL_FALSE);
}

void AtomViz::pointerMoveEvent(PointerMoveEvent& event) {
    if (_imgui.handlePointerMoveEvent(event)) {
        /* Prevent ImGui from capturing the pointer */
        event.setAccepted();
        return;
    }

    if (!event.isPrimary() || !(event.pointers() & (Pointer::MouseLeft|Pointer::Finger))) return;

    if (event.modifiers() & InputEvent::Modifier::Shift)
        _arcballCamera->translate(event.position());
    else
        _arcballCamera->rotate(event.position());

    event.setAccepted();
    redraw(); // Camera has changed, redraw!
}

void AtomViz::scrollEvent(ScrollEvent& event) {
    if (_imgui.handleScrollEvent(event)) {
        /* Prevent scrolling the page */
        event.setAccepted();
        return;
    }

    const float delta = event.offset().y();
    if (Math::abs(delta) < 1.0e-2f) return;

    _arcballCamera->zoom(delta);

    event.setAccepted();
    redraw(); // Camera has changed, redraw!
}

void AtomViz::textInputEvent(TextInputEvent &event)
{
    if (_imgui.handleTextInputEvent(event)) {
        /* Prevent ImGui from capturing the text input */
        event.setAccepted();
        return;
    }

    event.setAccepted();
}

MAGNUM_APPLICATION_MAIN(AtomViz)