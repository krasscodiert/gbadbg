#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl2.h"
#include <cstdio>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <GLFW/glfw3.h>

#define VSYNC_ENABLED false


#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;
    GLFWwindow* window = glfwCreateWindow(1270, 720, "gbadbg", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);

    if(VSYNC_ENABLED)
        glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();

    ImVec4 clear_color(0.1f, 0.1f, 0.1f, 0xFF);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            /*
             *  Main UI Window
            */

            auto tsize = ImGui::CalcTextSize("GBADBG IZZ DA");
            auto dl = ImGui::GetOverlayDrawList();
            bool held, hovered;
            ImGui::ButtonBehavior(ImRect(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2) - ImVec2(tsize.x , tsize.x), ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2) + ImVec2(tsize.x, tsize.x)), ImGui::GetID("yoaaa"), &hovered, &held);
            if(hovered){
                dl->AddCircleFilled(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2), tsize.x, IM_COL32(0xd9, 0x52, 0xb1, 0xff), 400);
                dl->AddText(ImVec2((io.DisplaySize.x / 2) - tsize.x / 2, io.DisplaySize.y / 2), IM_COL32(0x58, 0x86, 0xd9, 0xff), "GBADBG IZZ DA");
            } else {
                dl->AddCircle(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2), tsize.x, IM_COL32(0x58, 0x86, 0xd9, 0xff), 400);
                dl->AddText(ImVec2((io.DisplaySize.x / 2) - tsize.x / 2, io.DisplaySize.y / 2), IM_COL32(0xd9, 0x52, 0xb1, 0xff), "GBADBG IZZ DA");
            }


        }
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}