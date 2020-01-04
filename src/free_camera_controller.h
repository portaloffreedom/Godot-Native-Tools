#pragma once

#include <Godot.hpp>
#include <Camera.hpp>

namespace godot {

class FreeCameraController: public Camera {
    GODOT_CLASS(FreeCameraController, Camera)

public:
    static void _register_methods();

    FreeCameraController();
    virtual ~FreeCameraController();

    void _init();
    void _ready();
    void _process(float delta);
    void _input(Variant event);

private:
    void set_mouse_capture(bool capture);

private:
    bool mouse_captured;
};

}