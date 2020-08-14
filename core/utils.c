#include "glfw.h"
#include "utils.h"

key_t glfw_to_engine_key(int glfw_key) {
  switch (glfw_key) {
  case GLFW_KEY_A :
    return A;
  case GLFW_KEY_B :
    return B;
  case GLFW_KEY_C :
    return C;
  case GLFW_KEY_D :
    return D;
  case GLFW_KEY_E :
    return E;
  case GLFW_KEY_F :
    return F;
  case GLFW_KEY_G :
    return G;
  case GLFW_KEY_H :
    return H;
  case GLFW_KEY_I :
    return I;
  case GLFW_KEY_J :
    return J;
  case GLFW_KEY_K :
    return K;
  case GLFW_KEY_L :
    return L;
  case GLFW_KEY_M :
    return M;
  case GLFW_KEY_N :
    return N;
  case GLFW_KEY_O :
    return O;
  case GLFW_KEY_P :
    return P;
  case GLFW_KEY_Q :
    return Q;
  case GLFW_KEY_R :
    return R;
  case GLFW_KEY_S :
    return S;
  case GLFW_KEY_T :
    return T;
  case GLFW_KEY_U :
    return U;
  case GLFW_KEY_V :
    return V;
  case GLFW_KEY_W :
    return W;
  case GLFW_KEY_X :
    return X;
  case GLFW_KEY_Y :
    return Y;
  case GLFW_KEY_Z :
    return Z;
  case GLFW_KEY_1 :
    return Kb1;
  case GLFW_KEY_2 :
    return Kb2;
  case GLFW_KEY_3 :
    return Kb3;
  case GLFW_KEY_4 :
    return Kb4;
  case GLFW_KEY_5 :
    return Kb5;
  case GLFW_KEY_6 :
    return Kb6;
  case GLFW_KEY_7 :
    return Kb7;
  case GLFW_KEY_8 :
    return Kb8;
  case GLFW_KEY_9 :
    return Kb9;
  case GLFW_KEY_0 :
    return Kb0;
  case GLFW_KEY_ENTER :
    return Enter;
  case GLFW_KEY_ESCAPE :
    return Escape;
  case GLFW_KEY_BACKSPACE :
    return Backspace;
  case GLFW_KEY_TAB :
    return Tab;
  case GLFW_KEY_SPACE :
    return Space;
  case GLFW_KEY_MINUS :
    return Minus;
  case GLFW_KEY_EQUAL :
    return Equals;
  case GLFW_KEY_LEFT_BRACKET :
    return LeftBracket;
  case GLFW_KEY_RIGHT_BRACKET :
    return RightBracket;
  case GLFW_KEY_BACKSLASH :
    return Backslash;
  case GLFW_KEY_SEMICOLON :
    return Semicolon;
  case GLFW_KEY_APOSTROPHE :
    return Apostrophe;
  case GLFW_KEY_GRAVE_ACCENT :
    return Grave;
  case GLFW_KEY_COMMA :
    return Comma;
  case GLFW_KEY_PERIOD :
    return Dot;
  case GLFW_KEY_SLASH :
    return Slash;
  case GLFW_KEY_CAPS_LOCK :
    return CapsLock;
  case GLFW_KEY_F1 :
    return F1;
  case GLFW_KEY_F2 :
    return F2;
  case GLFW_KEY_F3 :
    return F3;
  case GLFW_KEY_F4 :
    return F4;
  case GLFW_KEY_F5 :
    return F5;
  case GLFW_KEY_F6 :
    return F6;
  case GLFW_KEY_F7 :
    return F7;
  case GLFW_KEY_F8 :
    return F8;
  case GLFW_KEY_F9 :
    return F9;
  case GLFW_KEY_F10 :
    return F10;
  case GLFW_KEY_F11 :
    return F11;
  case GLFW_KEY_F12 :
    return F12;
  case GLFW_KEY_PRINT_SCREEN :
    return PrintScreen;
  case GLFW_KEY_SCROLL_LOCK :
    return ScrollLock;
  case GLFW_KEY_PAUSE :
    return Pause;
  case GLFW_KEY_INSERT :
    return Insert;
  case GLFW_KEY_HOME :
    return Home;
  case GLFW_KEY_PAGE_UP :
    return PageUp;
  case GLFW_KEY_DELETE :
    return Delete;
  case GLFW_KEY_END :
    return End;
  case GLFW_KEY_PAGE_DOWN :
    return PageDown;
  case GLFW_KEY_RIGHT :
    return Right;
  case GLFW_KEY_LEFT :
    return Left;
  case GLFW_KEY_DOWN :
    return Down;
  case GLFW_KEY_UP :
    return Up;
  case GLFW_KEY_NUM_LOCK :
    return NumLock;
  case GLFW_KEY_KP_DIVIDE :
    return NpDivide;
  case GLFW_KEY_KP_MULTIPLY :
    return NpMultiply;
  case GLFW_KEY_KP_SUBTRACT :
    return NpMinus;
  case GLFW_KEY_KP_ADD :
    return NpPlus;
  case GLFW_KEY_KP_ENTER :
    return NpEnter;
  case GLFW_KEY_KP_1 :
    return Np1;
  case GLFW_KEY_KP_2 :
    return Np2;
  case GLFW_KEY_KP_3 :
    return Np3;
  case GLFW_KEY_KP_4 :
    return Np4;
  case GLFW_KEY_KP_5 :
    return Np5;
  case GLFW_KEY_KP_6 :
    return Np6;
  case GLFW_KEY_KP_7 :
    return Np7;
  case GLFW_KEY_KP_8 :
    return Np8;
  case GLFW_KEY_KP_9 :
    return Np9;
  case GLFW_KEY_KP_0 :
    return Np0;
  case GLFW_KEY_KP_DECIMAL :
    return NpDot;
  case GLFW_KEY_LEFT_SUPER:
  case GLFW_KEY_RIGHT_SUPER :
    return Super;
  case GLFW_KEY_LEFT_SHIFT :
    return LeftShift;
  case GLFW_KEY_LEFT_CONTROL :
    return LeftControl;
  case GLFW_KEY_LEFT_ALT :
    return LeftAlt;
  case GLFW_KEY_RIGHT_ALT :
    return RightAlt;
  case GLFW_KEY_RIGHT_CONTROL :
    return RightControl;
  case GLFW_KEY_RIGHT_SHIFT :
    return RightShift;
  default :
    return Unknown;
  }
}

action_state_t glfw_to_engine_action(int glfw_button_state) {
  switch (glfw_button_state) {
  case GLFW_PRESS:
    return Pressed;
  case GLFW_RELEASE:
    return Released;
  case GLFW_REPEAT:
    return Repeated;
  default:
    return NbAction;
  }
}

modifiers_t glfw_to_engine_modifiers(int mods) {
  return (modifiers_t) {
      mods & GLFW_MOD_CONTROL,
      mods & GLFW_MOD_ALT,
      mods & GLFW_MOD_SHIFT,
      mods & GLFW_MOD_SUPER,
      mods & GLFW_MOD_NUM_LOCK,
      mods & GLFW_MOD_CAPS_LOCK,
  };
}

mouse_button_t glfw_to_engine_mouse_button(int glfw_button) {
  switch (glfw_button) {
  case GLFW_MOUSE_BUTTON_RIGHT:
    return RightButton;
  case GLFW_MOUSE_BUTTON_MIDDLE:
    return MiddleButton;
  case GLFW_MOUSE_BUTTON_LEFT:
    return LeftButton;
  default:
    return NbMouseButton;
  }
}
