#include "RenderTexture.hpp"
#include "game_renderer.hpp"
#include "game_resources.hpp"
#include "keybinds.hpp"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include "scene.hpp"
#include "scene_manager.hpp"

int main() {
  raylib::Window window = raylib::Window(1280, 720, "Game ");

  window.SetTargetFPS(60);

  GameRenderer::Init(1280, 720);
  GameResources::LoadResources();
  sceneManager.SetScene(std::make_unique<MainMenu>());

  while (!window.ShouldClose() && !sceneManager.shouldExit) {
    // Update Logic Here ========================

    sceneManager.Update();

    // Drawing Logic Here =======================
    GameRenderer::Begin();

    sceneManager.Draw();

    GameRenderer::End();

    window.BeginDrawing();
    window.ClearBackground(BLACK);

    sceneManager.Draw();
    GameRenderer::Flip({});

    window.EndDrawing();
  }

  CloseWindow();

  return 0;
}