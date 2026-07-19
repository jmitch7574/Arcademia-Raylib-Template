#include "engine/input/action_map.hpp"
#include "engine/input/arcademia_keybinds.hpp"
#include "engine/input/input_manager.hpp"
#include "game_renderer.hpp"
#include <raylib.h>
#include <vector>

ActionMap::ActionDebugScene::ActionDebugScene() {}

ActionMap::ActionDebugScene::~ActionDebugScene() {}

void ActionMap::ActionDebugScene::Update() {}

void ActionMap::ActionDebugScene::Draw() {
  float width = GameRenderer::GetWidth();

  float columnWidth = width / MAX_PLAYERS;

  // Draw Column Separators
  for (int i = 1; i < MAX_PLAYERS; i++) {
    DrawLine(columnWidth * i, 0, columnWidth * i, GameRenderer::GetHeight(),
             GRAY);
  }

  // Draw Columns
  for (int i = 0; i < MAX_PLAYERS; i++) {
    InputManager::PlayerInput player = InputManager::GetPlayerInfo(i);

    float xStart  = i * columnWidth;
    float xMax    = (i + 1) * columnWidth;
    float xWidth  = (xMax - xStart);
    float xCenter = xStart + (xWidth / 2);

    std::string titleText = TextFormat("Player %d", i + 1);
    float titleWidth      = MeasureText(titleText.c_str(), 20);

    Color col = WHITE;

    if (!player.isActive)
      col = GRAY;

    DrawText(titleText.c_str(), xStart + (xWidth - titleWidth) / 2, 25, 20,
             col);

    if (!player.isActive)
      return;

    std::string nameText = InputManager::GetFriendlyName(i);
    float nameWidth      = MeasureText(nameText.c_str(), 10);

    DrawText(nameText.c_str(), xStart + (xWidth - nameWidth) / 2, 50, 10,
             WHITE);

    int yOffset = 100;
    for (auto &buttonAction : ActionMap::ButtonDict) {
      Color col = ActionMap::IsActionDown(i, buttonAction.second) ? RED : GRAY;

      DrawCircle(xStart + 15, yOffset, 10, col);
      DrawText(buttonAction.first, xStart + 75, yOffset - 10, 20, WHITE);

      yOffset += 35;
    }

    constexpr int axisWidth = 45;
    for (auto &axisAction : ActionMap::AxisDict) {
      float axis       = ActionMap::GetAxis(i, axisAction.second);
      float lineOffset = (axisWidth / 2.0) + (axis * (axisWidth / 2.0));

      DrawRectangle(xStart + 15, yOffset - 10, axisWidth, 20, GRAY);
      DrawRectangle(xStart + 15 + (lineOffset - 5), yOffset - 10, 10, 20, RED);
      DrawText(axisAction.first, xStart + 75, yOffset - 10, 20, WHITE);

      yOffset += 35;
    }
  }
}