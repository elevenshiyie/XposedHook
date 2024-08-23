//
// Created by Eleven on 2024/4/28.
//

#include <android/native_window_jni.h>
#include <android/input.h>
#include <EGL/egl.h>
#include <unistd.h>
#include <thread>
#include <GLES3/gl3.h>
#include "modmenu_native.h"
#include "dobby.h"
#include "imgui_impl_android.h"
#include "imgui_impl_opengl3.h"
#include "Font.h"

static int g_GlHeight, g_GlWidth;
static bool g_init = false;
int m_sendOnTouchEvent = 0;
bool m_needClearMousePos = true;

void (*orig_initializeMotionEvent)(void *a1, void *a2, void *a3);
void initializeMotionEvent(void *a1, void *a2, void *a3)
{
    orig_initializeMotionEvent(a1,a2,a3);
    if (g_init)
    {
        ImGui_ImplAndroid_HandleInputEvent((AInputEvent *)a1,{(float)2400 / g_GlWidth, (float)1080 / g_GlHeight});
    }
}

extern "C"
{
JNIEXPORT void JNICALL
Java_com_eleven_xposedhook_NHook_init(JNIEnv *env, jclass clazz) {
    if (g_init)
        return;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = NULL;
    ImGui_ImplAndroid_Init();
    ImGui_ImplOpenGL3_Init("#version 300 es");
    ImGui::StyleColorsDark();

    io.Fonts->AddFontFromMemoryTTF((void*)OPPOSans_H, OPPOSans_H_size, 20.f, NULL, io.Fonts->GetGlyphRangesChineseFull());
    ImGui::GetStyle().ScaleAllSizes(3.0f);

    void *inputaddr = DobbySymbolResolver("/system/lib64/libinput.so","_ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE");
    DobbyHook((void*)inputaddr, (void *)initializeMotionEvent,(void **) &orig_initializeMotionEvent);

    g_init = true;
}

JNIEXPORT void JNICALL
Java_com_eleven_xposedhook_NHook_resize(JNIEnv *env, jclass clazz, jint width, jint height)
{
    g_GlHeight = height;
    g_GlWidth = width;
    glViewport(0, 0, width, height);
    ImGuiIO &io = ImGui::GetIO();
    ImGui::GetIO().DisplaySize = ImVec2((float) width, (float)height);
}

JNIEXPORT void JNICALL
Java_com_eleven_xposedhook_NHook_render(JNIEnv *env, jclass clazz) {
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
}