#include "free_camera_controller.h"
#include <Input.hpp>
#include <InputEventMouseMotion.hpp>

using namespace godot;

#define DEFAULT_SPEED 30.0
#define DEFAULT_MOUSE_SPEED 0.01

void FreeCameraController::_register_methods()
{
    register_property<FreeCameraController, float>("speed", &FreeCameraController::speed, DEFAULT_SPEED,
        GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_TYPE_STRING, "Camera movement speed");
    register_property<FreeCameraController, float>("mouse_speed", &FreeCameraController::mouse_speed, DEFAULT_MOUSE_SPEED,
        GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_TYPE_STRING, "Mouse movement speed");
    register_method("_ready", &FreeCameraController::_ready);
    register_method("_process", &FreeCameraController::_process);
    register_method("_input", &FreeCameraController::_input);
}

FreeCameraController::FreeCameraController()
    : mouse_captured(false)
    , speed(DEFAULT_SPEED)
    , mouse_speed(DEFAULT_MOUSE_SPEED)
{}

FreeCameraController::~FreeCameraController()
{}

void FreeCameraController::_init()
{}

void FreeCameraController::_ready()
{
    set_mouse_capture(true);
}

void FreeCameraController::_process(float delta)
{
    const float run_multiplier = 3.0;

    float movement_backwards = 0.0;
    float movement_sideways = 0.0;
    float rotation = 0.0;

    Input *input = Input::get_singleton();
    if (input->is_action_just_pressed("ui_cancel"))
    {
        this->set_mouse_capture(!this->mouse_captured);
    }

    if (this->mouse_captured)
    {
        bool up = input->is_action_pressed("ui_up");
        bool down = input->is_action_pressed("ui_down");
        bool left = input->is_action_pressed("ui_left");
        bool right = input->is_action_pressed("ui_right");
        bool rotate_left = input->is_action_pressed("rotate_left");
        bool rotate_right = input->is_action_pressed("rotate_right");
        bool run = input->is_action_pressed("run");

        if (up) movement_backwards -= 1.0;
        if (down) movement_backwards += 1.0;
        if (left) movement_sideways -= 1.0;
        if (right) movement_sideways += 1.0;
        if (rotate_left) rotation += 1.0;
        if (rotate_right) rotation -= 1.0;

        if (up || down || left || right)
        {
            Vector3 movement = Vector3(
                movement_sideways,
                0.0f,
                movement_backwards
            ) * speed * delta;

            if (run) movement *= run_multiplier;

            this->translate(movement);
        }

        if (rotate_left || rotate_right)
        {
            this->rotate_y(rotation * delta);
        }
    }

}

void FreeCameraController::_input(const Variant variant_event)
{
    if (this->mouse_captured) {
        Ref<InputEventMouseMotion> event = variant_event;
        if (event.is_valid()) {
            Vector2 relative_motion = event->get_relative() * this->mouse_speed;
            this->rotate_object_local(Vector3(1.0, 0.0, 0.0), -relative_motion.y);
            this->rotate_y(-relative_motion.x);
        }
    }
}

void FreeCameraController::set_mouse_capture(const bool capture)
{
    if (this->mouse_captured == capture)
        return;

    this->mouse_captured = capture;
    Input *input = Input::get_singleton();
    input->set_mouse_mode(capture ? Input::MOUSE_MODE_CAPTURED : Input::MOUSE_MODE_VISIBLE);
}