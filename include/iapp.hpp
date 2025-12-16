#ifndef APPI_HPP
#define APPI_HPP

#include "imgui.h"

#define __GLFW_OPENGL3
#include "backends.hpp"

template <typename Derived> class IApp {
public:
  Window_backend window = nullptr;
  ImVec4 clear_color;
  ImGuiIO *io = nullptr;
  void run() { static_cast<Derived *>(this)->run(); }

private:
  friend Derived;
  IApp() { init(); }
  ~IApp() { cleanup(); }
  int init() {

    const char *glsl_version = init_backend();
    window = CreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr,
                          nullptr);
    if (window == nullptr)
      return 1;
    MakeWindowCurrent(window);
    SwapBuffersInterval(1); // Enable vsync
    // HideWindow(window);     // hide main window

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    (void)io;
    io->ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io->ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    io->ConfigFlags |=
        ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform
                                          // Windows
    // io->ConfigViewportsNoAutoMerge = true;
    // io->ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform
    // windows can look identical to regular ones.
    ImGuiStyle &style = ImGui::GetStyle();
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      style.WindowRounding = 0.0f;
      style.Colors[ImGuiCol_WindowBg].w = 0.0f;
    }

    SetupRendererBackend(window, glsl_version);
    // Our state
    // ImGui::GetIO().Fonts->AddFontFromFileTTF("E:/Projects/Solution/imguiTemplate/fonts/Roboto-Medium.ttf",
    // 24.0f);
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    return 0;
  }
  void cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    DestroyWindow(window);
    Terminate();
  }
};
#endif
