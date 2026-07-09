#pragma once
#include "raylib.h"
#include <vector>

class GameRenderer {
public:
  static RenderTexture2D tex;
  static void Init(int width, int height);
  static void Begin();
  static void End();
  static void Flip(std::vector<Shader *> shaders);
  static int GetWidth();
  static int GetHeight();
};