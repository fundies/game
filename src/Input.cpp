#include "Input.hpp"
#include "Logger.hpp"

std::map<int, bool> Input::_keyPressed;
std::map<int, bool> Input::_keyHeld;
std::map<int, bool> Input::_keyReleased;

Gamepad Input::_gamepad[4];
SDL_GameController* Input::_controllers[4] = {nullptr, nullptr, nullptr, nullptr};

ControlScheme Input::_controls;

Gamepad::Gamepad()
    : isConnected(false),
      deadzone(0.5f),
      _buttonPressed{false},
      _buttonHeld{false},
      _buttonReleased{false},
      _axisPressed{false},
      _axisHeld{false},
      _axisReleased{false},
      _axes{0} {}

bool Gamepad::Left() { return ((_axes[0] < -deadzone) || (_axes[6] < -deadzone)); }

bool Gamepad::Right() { return ((_axes[0] > deadzone) || (_axes[6] > deadzone)); }

bool Gamepad::Up() { return ((_axes[1] < -deadzone) || (_axes[7] < -deadzone)); }

bool Gamepad::Down() { return ((_axes[1] > deadzone) || (_axes[7] > deadzone)); }

bool Gamepad::ButtonPressed(GamepadButton id) {
  if (!isConnected) return false;

  switch (id) {
    default:
      return false;

    case GamepadButton::A:
      return _buttonPressed[0];

    case GamepadButton::B:
      return _buttonPressed[1];

    case GamepadButton::X:
      return _buttonPressed[2];

    case GamepadButton::Y:
      return _buttonPressed[3];

    case GamepadButton::Left:
      return Left() && (_axisPressed[0] || _axisPressed[6]);

    case GamepadButton::Right:
      return Right() && (_axisPressed[0] || _axisPressed[6]);

    case GamepadButton::Up:
      return Up() && (_axisPressed[1] || _axisPressed[7]);

    case GamepadButton::Down:
      return Down() && (_axisPressed[1] || _axisPressed[7]);
  }
}

bool Gamepad::ButtonHeld(GamepadButton id) {
  if (!isConnected) return false;

  switch (id) {
    default:
      return false;

    case GamepadButton::A:
      return _buttonHeld[0];

    case GamepadButton::B:
      return _buttonHeld[1];

    case GamepadButton::X:
      return _buttonHeld[2];

    case GamepadButton::Y:
      return _buttonHeld[3];

    case GamepadButton::Left:
      return Left();

    case GamepadButton::Right:
      return Right();

    case GamepadButton::Up:
      return Up();

    case GamepadButton::Down:
      return Down();
  }
}

bool Gamepad::ButtonReleased(GamepadButton id) { return false; }

void Gamepad::UpdateAxes() {
  for (unsigned j = 0; j < SDL_CONTROLLER_AXIS_MAX; j++) {
    if (std::abs(_axes[j]) > deadzone) {
      if (_axisHeld[j])
        _axisPressed[j] = false;
      else
        _axisPressed[j] = true;

      _axisHeld[j] = true;
      _axisReleased[j] = false;
    } else {
      if (_axisHeld[j]) _axisReleased[j] = true;

      _axisPressed[j] = false;
      _axisHeld[j] = false;
    }
  }
}

void Gamepad::SetAxisValue(int axis, float value) {
  _axes[axis] = value;
}

void Gamepad::SetGamepadDown(int btn) {
  _buttonPressed[btn] = true;
  _buttonHeld[btn] = true;
  _buttonReleased[btn] = false;
}

void Gamepad::SetGamepadUp(int btn) {
  _buttonReleased[btn] = true;
  _buttonPressed[btn] = false;
  _buttonHeld[btn] = false;
}

void Input::GamepadDown(int id, int btn) {
  _gamepad[id].SetGamepadDown(btn);
}

void Input::GamepadUp(int id, int btn) {
  _gamepad[id].SetGamepadUp(btn);
}

Input& Input::Get() {
  static Input instance;
  return instance;
}

void Input::KeyDown(int key) {
  _keyPressed[key] = true;
  _keyHeld[key] = true;
  _keyReleased[key] = false;
}

void Input::KeyUp(int key) {
  _keyReleased[key] = true;
  _keyPressed[key] = false;
  _keyHeld[key] = false;
}

void Input::ResetButtons() {
  for (auto&& k : _keyPressed) {
    k.second = false;
  }

  for (unsigned i = 0; i < 4; i++) {
		if (_gamepad[i].isConnected) {
			_gamepad[i].UpdateAxes();
    }
  }


			/*int buttonCount;
			auto buttons = glfwGetJoystickButtons(i, &buttonCount);
			_gamepad[i].UpdateButtons(buttons, buttonCount);
		}
	}*/
}

bool Input::ButtonPressed(GameControl id) {
  return _keyPressed[_controls.GetButton(id).key] || _gamepad[0].ButtonPressed(_controls.GetButton(id).button);
}

bool Input::ButtonHeld(GameControl id) {
  return _keyHeld[_controls.GetButton(id).key] || _gamepad[0].ButtonHeld(_controls.GetButton(id).button);
}

bool Input::ButtonReleased(GameControl id) { return _keyReleased[_controls.GetButton(id).key]; }

void Input::SetControlScheme(ControlScheme& controls) { _controls = controls; }

void Input::BindController(int id) {
  _controllers[id] = SDL_GameControllerOpen(id);
  _gamepad[id].isConnected = true;
}

void Input::SetAxisValue(int ctrlrID, int axis, float value) {
  _gamepad[ctrlrID].SetAxisValue(axis, value);
}
