#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "themes.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1400, 800, "Volleyball Manager", NULL, NULL);
    if (!window) 
    {
        std::cout << "Failed to create window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) 
    {
        std::cout << "Failed to load pointer." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.Fonts->AddFontFromFileTTF("src/assets/fonts/SpaceMono-Regular.ttf", 20);
    io.Fonts->AddFontFromFileTTF("src/assets/fonts/SpaceMono-Bold.ttf", 20);
    ImGui::StyleColorsDark();
    darkTheme();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("DockSpace", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus);
        ImGui::PopStyleVar(3);
        ImGuiID dockspace_id = ImGui::GetID("Dockspace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoResize | ImGuiDockNodeFlags_AutoHideTabBar);
        ImGui::End();

        ImGui::Begin("Volleyball Manager", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
        
        ImGui::PushFont(io.Fonts->Fonts[1]);
        ImVec2 window_size = ImGui::GetWindowSize();
        ImVec2 button_size = ImVec2(200.0f, 80.0f);
        ImVec2 button_pos = ImVec2((window_size.x - button_size.x) * 0.5f, (window_size.y - (2 * button_size.y) + 10.0f) * 0.5f);
        ImGui::SetCursorPos(button_pos);
        if (ImGui::Button("Start New Career", button_size))
        {
            std::cout << "Soon..." << std::endl;
        }

        button_pos = ImVec2(button_pos.x, button_pos.y + button_size.y + 10.0f);
        ImGui::SetCursorPos(button_pos);
        if (ImGui::Button("Settings", ImVec2(200.0f, 80.0f)))
        {
            std::cout << "Soon..." << std::endl;
        }

        button_pos = ImVec2(button_pos.x, button_pos.y + button_size.y + 10.0f);
        ImGui::SetCursorPos(button_pos);
        if (ImGui::Button("Quit", ImVec2(200.0f, 80.0f)))
        {
            return -1;
        }
        ImGui::PopFont();

        ImGui::End();

        /* ImGui::ShowDemoWindow(); */

        ImGui::Render();
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}