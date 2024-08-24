package com.eleven.xposedhook;
import android.content.Context;

public class NHook
{
    public static boolean loadSo(Context context)
    {
        /*File file = context.getFileStreamPath("libnhook.so"); System.load(file.getAbsolutePath()); */
        System.loadLibrary("wind");
        return true;
    }

    public static native void init();

    public static native void resize(int width, int height);

    public static native void render();
}
