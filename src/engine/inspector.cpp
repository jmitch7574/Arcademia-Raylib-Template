#include "inspector.hpp"
#include "imgui.h"
#include "rlImGui.h"

void Inspector::Init() { rlImGuiSetup(true); }

void Inspector::Shutdown() { rlImGuiShutdown(); }

void Inspector::BeginFrame() { rlImGuiBegin(); }

void Inspector::EndFrame() { rlImGuiEnd(); }

void Inspector::RegisterInspector(IInspector *inspector) {
  for (auto &item : activeInspectors) {
    if (item == inspector) {
      return;
    }
  }
  activeInspectors.push_back(inspector);
}

void Inspector::UnregisterInspector(IInspector *inspector) {
  for (auto it = activeInspectors.begin(); it != activeInspectors.end(); ++it) {
    if (*it == inspector) {
      activeInspectors.erase(it);
      return;
    }
  }
}

void Inspector::DrawInspector() {
  BeginFrame();

  // Initialise Window and Tabs
  ImGui::Begin("Inspector");
  if (ImGui::BeginTabBar("SystemTabs")) {
    // Draw Engine Tab
    DrawEngineTab();

    // Draw Individual Systems
    for (auto *sys : activeInspectors) {
      if (ImGui::BeginTabItem(sys->GetName())) {
        sys->DrawInspector();
        ImGui::EndTabItem();
      }
    }
    ImGui::EndTabBar();
  }

  ImGui::End();
  EndFrame();
}

void Inspector::DrawEngineTab() {
  if (ImGui::BeginTabItem("Engine")) {
    ImGui::Checkbox("Pause when Open", &pauseWhenOpen);
    ImGui::EndTabItem();
  }
}

bool Inspector::IsOpen() { return isOpen; }

bool Inspector::ShouldPauseGame() { return isOpen && pauseWhenOpen; }

void Inspector::Toggle() { isOpen = !IsOpen(); }