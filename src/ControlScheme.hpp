#ifndef CONTROLSCHEME_HPP
#define CONTROLSCHEME_HPP

#include <map>
#include <string>
#include <vector>

#include "Types.hpp"

enum class GameControl : int { Left, Right, Up, Down, A, B, X, Y, Start, Select };

enum class GamepadButton : int { Invalid, Left, Right, Up, Down, A, B, X, Y, Start, Select };

class ButtonCtrl {
 public:
  ButtonCtrl(int key, GamepadButton button) : key(key), button(button) {}

  ButtonCtrl() : key(-1), button(GamepadButton::Invalid) {}
  int key;
  GamepadButton button;
};

class ControlScheme {
 public:
  ControlScheme();
  void SetButton(GameControl id, ButtonCtrl ctrl);
  const ButtonCtrl& GetButton(GameControl id) const;
  void PrintControls() const;
  void WriteConfig(std::string fname) const;
  bool ReadConfig(std::string fname);

 protected:
  std::map<GameControl, ButtonCtrl> _controls;
};

#endif
