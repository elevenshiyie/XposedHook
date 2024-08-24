package com.eleven.xposedhook;

import android.app.Activity;
import android.app.Application;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.content.Context;
import android.os.Bundle;

import de.robv.android.xposed.XC_MethodHook;
import de.robv.android.xposed.XposedHelpers;

public class HookUtils {

    interface InitCallback {
        void onHook(Context context);
    }

    public static void attachApplication(InitCallback callback) {
        // hook application attach
        XposedHelpers.findAndHookMethod(Application.class, "attach", Context.class, new XC_MethodHook() {
            @Override
            protected void afterHookedMethod(MethodHookParam param) throws Throwable {
                // get the context
                Context context = (Context) param.args[0];
                callback.onHook(context);
            }
        });
    }

    public static void attachActivity(InitCallback callback) {
        XposedHelpers.findAndHookMethod(Activity.class, "onCreate", Bundle.class, new XC_MethodHook() {
            @Override
            protected void afterHookedMethod(MethodHookParam param) throws Throwable {
                Activity activity = (Activity) param.thisObject;
                callback.onHook(activity);
            }
        });
    }

    public static void nativeHookInit(Context context)
    {
        if (!NHook.loadSo(context))
        {
            new Handler(Looper.getMainLooper()).postDelayed(() ->
            {
                nativeHookInit(context);
            }, 1000);
        }
    }

    private static final String TAG = "HookUtils";
}
