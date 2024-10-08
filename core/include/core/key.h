#pragma once

#include <stdbool.h>

typedef enum {
  Unknown = 0,
  Escape,
  F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
  PrintScreen, ScrollLock, Pause, Insert, Home, PageUp, PageDown, End,
  Delete, Up, Down, Left, Right,
  NumLock, NpDivide, NpMultiply, NpMinus, NpPlus, NpEnter, NpDot, Grave,
  Np0, Np1, Np2, Np3, Np4, Np5, Np6, Np7, Np8, Np9,
  Kb0, Kb1, Kb2, Kb3, Kb4, Kb5, Kb6, Kb7, Kb8, Kb9,
  Minus, Equals, RightBracket, LeftBracket,
  A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
  Comma, Dot, Semicolon, Slash, Backslash, Apostrophe, Tab, CapsLock,
  LeftShift, LeftControl, Super, LeftAlt, Space, RightAlt, RightControl, RightShift,
  Enter, Backspace,
  NbKey
} Key;

typedef enum {
  LeftButton = 0,
  MiddleButton,
  RightButton,
  NbMouseButton
} MouseButton;

typedef enum {
  Pressed = 0,
  Released,
  Repeated,
  NbAction
} ActionState;

typedef struct {
  bool ctrl: 1;
  bool alt: 1;
  bool shift: 1;
  bool super: 1;
  bool num_lock: 1;
  bool caps_lock: 1;
} Modifiers;
