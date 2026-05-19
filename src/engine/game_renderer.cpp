#include "game_renderer.hpp"
#include "raylib.h"

RenderTexture2D GameRenderer::tex;

void GameRenderer::Init(int width, int height) {
  tex = LoadRenderTexture(width, height);
}

void GameRenderer::Begin() {
  BeginTextureMode(tex);
  ClearBackground(BLACK);
}

void GameRenderer::End() { EndTextureMode(); }

void GameRenderer::Flip(std::vector<raylib::Shader *> shaders) {
  for (int i = 0; i < shaders.size(); i++) {
    shaders[i]->BeginMode();
  }

  DrawTextureRec(tex.texture,
                 Rectangle(0, 0, tex.texture.width, -tex.texture.height),
                 Vector2(0, 0), WHITE);

  for (int j = 0; j < shaders.size(); j++) {
    shaders[j]->EndMode();
  }
}

int GameRenderer::GetWidth() { return tex.texture.width; }

int GameRenderer::GetHeight() { return tex.texture.height; }