#pragma once

#include <core/key.h>

Key glfw_to_engine_key(int glfw_key);
ActionState glfw_to_engine_action(int glfw_button_state);
Modifiers glfw_to_engine_modifiers(int glfw_mods);
MouseButton glfw_to_engine_mouse_button(int glfw_button);



