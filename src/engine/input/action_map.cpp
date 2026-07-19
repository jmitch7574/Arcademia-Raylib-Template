#include "engine/input/action_map.hpp"

bool ActionMap::IsActionPressed(int playerIdx,
                                const InputManager::ButtonAction &action) {
  InputManager::PlayerInput player = InputManager::GetPlayerInfo(playerIdx);

  if (player.isKeyboard) {
#if ARCADEMIA
    return IsKeyPressed(action.arcademiaButtons[player.inputIdx]);
#else
    return IsKeyPressed(action.keyboardButton[player.inputIdx]);
#endif
  } else {
    return IsGamepadButtonPressed(player.inputIdx, action.controllerButton);
  }
}

bool ActionMap::IsActionDown(int playerIdx,
                             const InputManager::ButtonAction &action) {
  InputManager::PlayerInput player = InputManager::GetPlayerInfo(playerIdx);

  if (player.isKeyboard) {
#if ARCADEMIA
    return IsKeyDown(action.arcademiaButtons[player.inputIdx]);
#else
    return IsKeyDown(action.keyboardButton[player.inputIdx]);
#endif
  } else {
    return IsGamepadButtonDown(player.inputIdx, action.controllerButton);
  }
}

bool ActionMap::IsActionReleased(int playerIdx,
                                 const InputManager::ButtonAction &action) {
  InputManager::PlayerInput player = InputManager::GetPlayerInfo(playerIdx);

  if (player.isKeyboard) {
#if ARCADEMIA
    return IsKeyReleased(action.arcademiaButtons[player.inputIdx]);
#else
    return IsKeyReleased(action.keyboardButton[player.inputIdx]);
#endif
  } else {
    return IsGamepadButtonReleased(player.inputIdx, action.controllerButton);
  }
}

float ActionMap::GetAxis(int playerIdx,
                         const InputManager::AxisAction &action) {
  InputManager::PlayerInput player = InputManager::GetPlayerInfo(playerIdx);

  if (player.isKeyboard) {
#if ARCADEMIA
    return IsKeyDown(action.positiveArcademiaInput[player.inputIdx]) -
           IsKeyDown(action.negativeArcademiaInput[player.inputIdx]);
#else
    return IsKeyDown(action.positiveKeyboardInput[player.inputIdx]) -
           IsKeyDown(action.negativeKeyboardInput[player.inputIdx]);
#endif
  } else {
    return GetGamepadAxisMovement(player.inputIdx, action.controllerAxis);
  }
}