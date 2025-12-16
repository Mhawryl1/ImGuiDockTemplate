#include "iapp.hpp"

class App : public IApp<App>
{

  public:
    void run()
    {

#ifdef __EMSCRIPTEN__
        // For an Emscripten build we are disabling file-system access, so let's not
        // attempt to do a fopen() of the imgui.ini file. You may manually call
        // LoadIniSettingsFromMemory() to load settings from your own storage.
        io.IniFilename = nullptr;
        EMSCRIPTEN_MAINLOOP_BEGIN
#else
        while (!WindwoShoulClose(window))
#endif
        {
            PollEvents();
#ifdef __GLFW_OPENGL3
            if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
                ImGui_ImplGlfw_Sleep(10);
                continue;
            }
#endif
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ShowRoot();
            if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!"
                                               // and append into it.

                ImGui::Text("This is some useful text."); // Display some text (you can
                                                          // use a format strings too)
                ImGui::Checkbox("Demo Window",
                    &show_demo_window); // Edit bools storing our window
                                        // open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("float", &f, 0.0f,
                    1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color",
                    (float *)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets
                                             // return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
                ImGui::End();
            }
            {

                if (show_another_window) {
                    ImGui::Begin("Another Window",
                        &show_another_window); // Pass a pointer to our bool variable (the
                                               // window will have a closing button that
                                               // will clear the bool when clicked)
                    ImGui::Text("Hello from another window!");
                    if (ImGui::Button("Close Me")) show_another_window = false;
                    ImGui::End();
                }
            }
            // Rendering
            ImGui::Render();

            int display_w, display_h;
            GetFramebufferSize(window, &display_w, &display_h);
            Viewport(0, 0, display_w, display_h);
            ClearColor(0.0f, 0.0f, 0.0f, 0.0f); // FULLY TRANSPARENT
            UpdateAndRender(io);
            SwapBuffers(window);
        }

#ifdef __EMSCRIPTEN__
        EMSCRIPTEN_MAINLOOP_END;
#endif
    }

  private:
    void ShowRoot()
    {
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking
            | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        const ImGuiViewport *vp = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(vp->Pos);
        ImGui::SetNextWindowSize(vp->Size);
        ImGui::SetNextWindowViewport(vp->ID);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
        ImGui::Begin("Root", nullptr, flags);
        ImGuiDockNodeFlags dock_flags = ImGuiDockNodeFlags_PassthruCentralNode; // Make dock space window transparent
        ImGui::DockSpace(ImGui::GetID("RootDock"), ImVec2(0, 0), dock_flags);
        ImGui::End();
        ImGui::PopStyleColor();
    }

  private:
    bool show_demo_window = true;
    bool show_another_window = false;
};
