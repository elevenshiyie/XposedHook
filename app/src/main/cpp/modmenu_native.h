//
// Created by Eleven on 2024/4/28.
//

#ifndef XPOSEDNHOOK_MODMENU_NATIVE_H
#define XPOSEDNHOOK_MODMENU_NATIVE_H

#include "imgui.h"
#include <GLES3/gl3.h>

#include <android/log.h>
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "MainHook", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "MainHook", __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "MainHook", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, "MainHook", __VA_ARGS__)


#endif //XPOSEDNHOOK_MODMENU_NATIVE_H
