#include "ControlScheme.hpp"

#include <SDL.h>

ControlScheme::ControlScheme() {
  _controls[GameControl::Left] = ButtonCtrl(SDLK_LEFT, GamepadButton::Left);
  _controls[GameControl::Right] = ButtonCtrl(SDLK_RIGHT, GamepadButton::Right);
  _controls[GameControl::Up] = ButtonCtrl(SDLK_UP, GamepadButton::Up);
  _controls[GameControl::Down] = ButtonCtrl(SDLK_DOWN, GamepadButton::Down);
  _controls[GameControl::A] = ButtonCtrl(SDLK_x, GamepadButton::A);
  _controls[GameControl::B] = ButtonCtrl(SDLK_z, GamepadButton::B);
  _controls[GameControl::X] = ButtonCtrl(SDLK_a, GamepadButton::X);
  _controls[GameControl::Y] = ButtonCtrl(SDLK_s, GamepadButton::Y);
  _controls[GameControl::Start] = ButtonCtrl(SDLK_RETURN, GamepadButton::Start);
  _controls[GameControl::Select] = ButtonCtrl(SDLK_RSHIFT, GamepadButton::Select);
}

void ControlScheme::SetButton(GameControl id, ButtonCtrl ctrl) { _controls[id] = ctrl; }

const ButtonCtrl& ControlScheme::GetButton(GameControl id) const { return _controls.at(id); }

void ControlScheme::PrintControls() const {}

void ControlScheme::WriteConfig(std::string fname) const {}

bool ControlScheme::ReadConfig(std::string fname) { return false; }
