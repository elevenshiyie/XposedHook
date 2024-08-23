//
// Created by Eleven on 2024/8/23.
//

#include "wind.h"
#include "modmenu_native.h"
#include <unistd.h>
#include <dlfcn.h>

extern "C"
{
JNIEXPORT void JNICALL
Java_com_eleven_xposedhook_NHook_initNativeHook(JNIEnv *env, jclass thiz, jobject context)
{
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