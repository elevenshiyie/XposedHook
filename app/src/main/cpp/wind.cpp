//
// Created by Eleven on 2024/8/23.
//

#include "wind.h"
#include "modmenu_native.hpp"
#include <unistd.h>
#include <dlfcn.h>

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
    Java_com_eleven_xposedhook_NHook_init(JNIEnv *env, jclass clazz)
    {
        InitImGui();
        void *inputaddr = DobbySymbolResolver("/system/lib64/libinput.so", "_ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE");
        DobbyHook((void *) inputaddr, (void *) initializeMotionEvent, (void **) &orig_initializeMotionEvent);
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
    Java_com_eleven_xposedhook_NHook_render(JNIEnv *env, jclass clazz)
    {
        RenderImGui();
    }

    JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved)
    {
        JNIEnv *env;
        if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK)
        {
            return -1;
        }
        return JNI_VERSION_1_6;
    }
}