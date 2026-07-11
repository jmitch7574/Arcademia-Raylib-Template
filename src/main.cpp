#include "game_renderer.hpp"
#include "game_resources.hpp"
#include "imgui.h"
#include "inspector.hpp"
#include "keybinds.hpp"
#include "raylib.h"
#include "rlImGui.h"
#include "scene.hpp"
#include "scene_manager.hpp"
#include <vector>

int main() {
  InitWindow(1280, 720, "Game ");

  SetTargetFPS(60);

  GameRenderer::Init(1280, 720);
  GameResources::LoadResources();

#ifdef RELEASE
  sceneManager.SetScene(std::make_unique<MainMenu>());
#endif

  Inspector::Init();

  sceneManager.SetScene(std::make_unique<MainMenu>());

  while (!WindowShouldClose() && !sceneManager.shouldExit) {
    // Update Logic Here ========================

    if (IsKeyPressed(KEYBINDS.inspector.key))
      Inspector::Toggle();

    if (!Inspector::ShouldPauseGame())
      sceneManager.Update();

    // Drawing Logic Here =======================
    GameRenderer::Begin();

    sceneManager.Draw();

    GameRenderer::End();

    BeginDrawing();
    ClearBackground(BLACK);

    if (Inspector::ShouldPauseGame()) {
      GameRenderer::Flip({&GameResources::Blur});
      DrawRectangleRec(
          Rectangle(0, 0, GameRenderer::GetWidth(), GameRenderer::GetHeight()),
          Color(0, 0, 0, 180));
    } else {
      GameRenderer::Flip({});
    }

    if (Inspector::IsOpen())
      Inspector::DrawInspector();

    EndDrawing();
  }

  Inspector::Shutdown();

  CloseWindow();

  return 0;
}