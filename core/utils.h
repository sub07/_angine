#pragma once

#include <core/key.h>

key_t glfw_to_engine_key(int glfw_key);
action_state_t glfw_to_engine_action(int glfw_button_state);
modifiers_t glfw_to_engine_modifiers(int glfw_mods);
mouse_button_t glfw_to_engine_mouse_button(int glfw_button);

