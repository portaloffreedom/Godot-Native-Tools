#include "free_camera_controller.h"
#include <Input.hpp>
#include <InputEventMouseMotion.hpp>

using namespace godot;

void FreeCameraController::_register_methods()
{
    register_method("_ready", &FreeCameraController::_ready);
    register_method("_process", &FreeCameraController::_process);
    register_method("_input", &FreeCameraController::_input);
}

FreeCameraController::FreeCameraController()
    : mouse_captured(false)
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
    const float speed = 30.0;
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
    Ref<InputEventMouseMotion> event = variant_event;
    Godot::print("is_null {}", event.is_null());
    Godot::print("is_valid {}", event.is_valid());
    if (event.is_valid()) {
        float mouse_speed = 0.01;
        Vector2 relative_motion = event->get_relative() * mouse_speed;
        this->rotate_object_local(Vector3(1.0, 0.0, 0.0), -relative_motion.y);
        this->rotate_y(-relative_motion.x);
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