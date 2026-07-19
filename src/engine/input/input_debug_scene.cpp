#include "engine/input/action_map.hpp"
#include "engine/input/arcademia_keybinds.hpp"
#include "engine/input/input_manager.hpp"
#include <raylib.h>
#include <vector>

const float leftStickDeadzoneX   = 0.1f;
const float leftStickDeadzoneY   = 0.1f;
const float rightStickDeadzoneX  = 0.1f;
const float rightStickDeadzoneY  = 0.1f;
const float leftTriggerDeadzone  = -0.9f;
const float rightTriggerDeadzone = -0.9f;

InputManager::GamepadDebugScene::GamepadDebugScene() {
  xboxTex = LoadTexture("resources/engine/input/xbox.png");
  gamepad = 0;
}

InputManager::GamepadDebugScene::~GamepadDebugScene() {
  UnloadTexture(xboxTex);
}

void InputManager::GamepadDebugScene::Update() {
  if (IsKeyPressed(KEY_LEFT) && gamepad > 0)
    gamepad--;
  if (IsKeyPressed(KEY_RIGHT))
    gamepad++;
}

void InputManager::GamepadDebugScene::Draw() {
  ClearBackground(BLACK);
  DrawText(TextFormat("Gamepad %d", gamepad), 5, 5, 10, WHITE);
  DrawText(TextFormat("Gamepad Name: %s", GetGamepadName(gamepad)), 5, 20, 10,
           WHITE);

  // Get axis values
  float leftStickX  = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X);
  float leftStickY  = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y);
  float rightStickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
  float rightStickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);
  float leftTrigger =
      GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER);
  float rightTrigger =
      GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER);

  // Calculate deadzones
  if (leftStickX > -leftStickDeadzoneX && leftStickX < leftStickDeadzoneX)
    leftStickX = 0.0f;
  if (leftStickY > -leftStickDeadzoneY && leftStickY < leftStickDeadzoneY)
    leftStickY = 0.0f;
  if (rightStickX > -rightStickDeadzoneX && rightStickX < rightStickDeadzoneX)
    rightStickX = 0.0f;
  if (rightStickY > -rightStickDeadzoneY && rightStickY < rightStickDeadzoneY)
    rightStickY = 0.0f;
  if (leftTrigger < leftTriggerDeadzone)
    leftTrigger = -1.0f;
  if (rightTrigger < rightTriggerDeadzone)
    rightTrigger = -1.0f;

  DrawTexture(xboxTex, 100, 100, DARKGRAY);

  // Draw buttons: xbox home
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE))
    DrawCircle(494, 189, 19, RED);

  // Draw buttons: basic
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT))
    DrawCircle(536, 250, 9, RED);
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_LEFT))
    DrawCircle(452, 250, 9, RED);
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
    DrawCircle(601, 251, 15, BLUE);
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
    DrawCircle(636, 287, 15, LIME);
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
    DrawCircle(672, 251, 15, MAROON);
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP))
    DrawCircle(636, 215, 15, GOLD);

  // Draw buttons: d-pad
  DrawRectangle(417, 302, 19, 71, BLACK);
  DrawRectangle(393, 328, 69, 19, BLACK);
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP))
    DrawRectangle(417, 302, 19, 26, RED);
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
    DrawRectangle(417, 302 + 45, 19, 26, RED);
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
    DrawRectangle(392, 328, 25, 19, RED);
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
    DrawRectangle(392 + 44, 328, 26, 19, RED);

  // Draw buttons: left-right back
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_1))
    DrawCircle(359, 161, 20, RED);
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_1))
    DrawCircle(636, 161, 20, RED);

  // Draw axis: left joystick
  Color leftGamepadColor = BLACK;
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_THUMB))
    leftGamepadColor = RED;
  DrawCircle(359, 252, 39, BLACK);
  DrawCircle(359, 252, 34, LIGHTGRAY);
  DrawCircle(359 + (int)(leftStickX * 20), 252 + (int)(leftStickY * 20), 25,
             leftGamepadColor);

  // Draw axis: right joystick
  Color rightGamepadColor = BLACK;
  if (IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_THUMB))
    rightGamepadColor = RED;
  DrawCircle(561, 337, 38, BLACK);
  DrawCircle(561, 337, 33, LIGHTGRAY);
  DrawCircle(561 + (int)(rightStickX * 20), 337 + (int)(rightStickY * 20), 25,
             rightGamepadColor);

  // Draw axis: left-right triggers
  DrawRectangle(270, 130, 15, 70, GRAY);
  DrawRectangle(704, 130, 15, 70, GRAY);
  DrawRectangle(270, 130, 15, (int)(((1 + leftTrigger) / 2) * 70), RED);
  DrawRectangle(704, 130, 15, (int)(((1 + rightTrigger) / 2) * 70), RED);
}