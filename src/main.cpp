#include "console.hpp"
#include "game_renderer.hpp"
#include "game_resources.hpp"
#include "keybinds.hpp"
#include "raylib.h"
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

  sceneManager.SetScene(std::make_unique<MainMenu>());
  while (!WindowShouldClose() && !sceneManager.shouldExit) {
    // Update Logic Here ========================
    if (!Console::Get().enabled)
      sceneManager.Update();
    Console::Get().Update();

    // Drawing Logic Here =======================
    GameRenderer::Begin();

    sceneManager.Draw();

    GameRenderer::End();

    BeginDrawing();
    ClearBackground(BLACK);

    if (Console::Get().enabled) {
      GameRenderer::Flip({&GameResources::Blur});
      DrawRectangleRec(
          Rectangle(0, 0, GameRenderer::GetWidth(), GameRenderer::GetHeight()),
          Color(0, 0, 0, 180));
      Console::Get().Draw();
    } else {
      GameRenderer::Flip({});
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}