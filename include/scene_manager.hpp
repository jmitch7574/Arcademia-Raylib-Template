#pragma once
#include "inspector.hpp"
#include "scene.hpp"
#include <memory>

class SceneManager : IInspector {
private:
  std::unique_ptr<Scene> currentScene;

public:
  bool shouldExit = false;

  SceneManager() {};

  ~SceneManager() {}

  void SetScene(std::unique_ptr<Scene> scene) {
    currentScene = std::move(scene);
  }

  void Update() {
    if (currentScene)
      currentScene->Update();
  }

  void Draw() {
    if (currentScene)
      currentScene->Draw();
  }

  void DrawInspector() override;
  const char *GetName() const override { return "Scene"; }

  void CloseGame() { shouldExit = true; }
};

extern SceneManager sceneManager;