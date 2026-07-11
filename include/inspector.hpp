#pragma once
#include <string>
#include <vector>

struct IInspector;

namespace Inspector {
  // System Initialisation and shut down
  void Init();
  void Shutdown();

  // Frame Initialisation and Ending
  void BeginFrame();
  void EndFrame();

  // Inspector Registry
  void RegisterInspector(IInspector *inspector);
  void UnregisterInspector(IInspector *inspector);

  // Drawing
  void DrawInspector();
  void DrawEngineTab();

  // Inspector State
  bool IsOpen();
  bool ShouldPauseGame();
  void Toggle();
} // namespace Inspector

struct IInspector {

  IInspector() { Inspector::RegisterInspector(this); }
  virtual ~IInspector() { Inspector::UnregisterInspector(this); }

  virtual void DrawInspector()        = 0;
  virtual const char *GetName() const = 0;
};

namespace {
  bool isOpen;
  bool pauseWhenOpen = true;

  //   struct InspectorRegistry {
  //     std::string key;
  //     IInspector *inspector;
  //   };

  std::vector<IInspector *> activeInspectors;
} // namespace
