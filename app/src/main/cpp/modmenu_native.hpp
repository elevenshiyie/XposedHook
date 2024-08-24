//
// Created by Eleven on 2024/4/28.
//

#ifndef XPOSEDNHOOK_MODMENU_NATIVE_H
#define XPOSEDNHOOK_MODMENU_NATIVE_H

#include <android/native_window_jni.h>
#include <android/input.h>
#include <EGL/egl.h>
#include <unistd.h>
#include <thread>
#include <GLES3/gl3.h>
#include <android/log.h>
#include "imgui.h"
#include <GLES3/gl3.h>
#include "dobby.h"
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3.h"
#include "Font.h"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "MainHook", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "MainHook", __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "MainHook", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, "MainHook", __VA_ARGS__)

static int g_GlHeight, g_GlWidth;
static bool g_init = false;

void InitImGui()
{
    if (g_init)
        return;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = NULL;
    ImGui_ImplAndroid_Init();
    ImGui_ImplOpenGL3_Init("#version 300 es");
    ImGui::StyleColorsClassic();

    io.Fonts->AddFontFromMemoryTTF((void *) OPPOSans_H, OPPOSans_H_size, 20.f, NULL, io.Fonts->GetGlyphRangesChineseFull());
    ImGui::GetStyle().ScaleAllSizes(3.0f);

    g_init = true;
}

void RenderImGui()
{
    ImGuiIO &io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(g_GlWidth, g_GlHeight);
    ImGui::NewFrame();

    ImGui::Begin("Demo");
    ImGui::Text("Hello, world!");
    ImGui::Text("By消失");

    ImGui::End();

    ImDrawList *draw_list = ImGui::GetBackgroundDrawList();
    draw_list->PushClipRectFullScreen();

    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

#endif //XPOSEDNHOOK_MODMENU_NATIVE_H
