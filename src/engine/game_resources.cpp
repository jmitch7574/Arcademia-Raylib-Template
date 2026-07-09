#include "game_resources.hpp"
#include "game_renderer.hpp"
#include "raylib.h"

Shader GameResources::Blur;

void GameResources::LoadResources() {
  Blur          = LoadShader(0, "resources/shaders/blur.fs");
  int widthLoc  = GetShaderLocation(Blur, "renderWidth");
  int heightLoc = GetShaderLocation(Blur, "renderHeight");

  int width  = GameRenderer::GetWidth();
  int height = GameRenderer::GetWidth();

  SetShaderValue(Blur, widthLoc, &width, SHADER_UNIFORM_INT);
  SetShaderValue(Blur, heightLoc, &height, SHADER_UNIFORM_INT);
}