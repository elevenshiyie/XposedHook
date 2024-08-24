package com.eleven.xposedhook;

import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;
import com.eleven.xposedhook.menu.NativeSuface;
import com.eleven.xposedhook.menu.CreateNativeWindow;
import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XC_MethodReplacement;
import de.robv.android.xposed.XposedHelpers;
import de.robv.android.xposed.callbacks.XC_LoadPackage;

public class MainHook implements IXposedHookLoadPackage {
    private static final String TAG = "MainHook";

    public static final boolean USE_NATIVE_MENU = true;

    private static final List<String> packageList = new ArrayList<String>()
    {
        { add("com.tencent.tmgp.cf"); }
    };

    @Override
    public void handleLoadPackage(XC_LoadPackage.LoadPackageParam lpparam) {
        if (lpparam.packageName.equals(BuildConfig.APPLICATION_ID)) {
            XposedHelpers.findAndHookMethod(BuildConfig.APPLICATION_ID + ".SettingsActivity",
                    lpparam.classLoader, "isModuleActive", XC_MethodReplacement.returnConstant(Boolean.TRUE));
        } else if (packageList.contains(lpparam.packageName)) {
            HookUtils.attachApplication(HookUtils::nativeHookInit);
            HookUtils.attachActivity(activity -> createNativeMenu(activity));
        }
    }

    private static void createNativeMenu(Context activity) {
        if (activity != null)
        {
            new Handler(Looper.getMainLooper()).post(() ->
            {
                try {
                    NativeSuface menu = new NativeSuface(activity);
                    CreateNativeWindow wind = new CreateNativeWindow(activity);
                    wind.CreateWindow();
                } catch (Exception e) {
                }
            });
        }
    }
}