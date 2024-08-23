package com.eleven.xposedhook.menu;

import android.app.Activity;
import android.app.Service;
import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.view.Gravity;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.WindowManager;

public class CreateNativeWindow extends SurfaceView implements SurfaceHolder.Callback {

    private boolean isFlag;

    private WindowManager windowManager;

    private GLSurfaceView glView;

    public Activity mCurrentActivity;

    public CreateNativeWindow(Context context)
    {
        super(context);
        mCurrentActivity = (Activity) context;
    }

    @Override
    public void surfaceCreated(SurfaceHolder p1) {
        isFlag = true;
    }

    @Override
    public void surfaceChanged(SurfaceHolder p1, int p2, int p3, int p4) {
        isFlag = true;
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder p1) {
        isFlag = false;
    }

    public void CreateWindow()
    {
        int LAYOUT_FLAG;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            LAYOUT_FLAG = WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY;
        } else {
            LAYOUT_FLAG = WindowManager.LayoutParams.TYPE_SYSTEM_OVERLAY;
        }
        final WindowManager.LayoutParams params = new WindowManager.LayoutParams(
                WindowManager.LayoutParams.MATCH_PARENT,
                WindowManager.LayoutParams.MATCH_PARENT, 0, 0,
                LAYOUT_FLAG,
                WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE
                        | WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE | WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN | WindowManager.LayoutParams.FLAG_FULLSCREEN | WindowManager.LayoutParams.FLAG_HARDWARE_ACCELERATED,
                PixelFormat.RGBA_8888);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P)
            params.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;

        params.gravity = Gravity.TOP | Gravity.START;
        params.x = 0;
        params.y = 0;

        windowManager = (WindowManager)mCurrentActivity.getApplicationContext().getSystemService(Service.WINDOW_SERVICE);

        glView = new NativeSuface(mCurrentActivity);
        windowManager.addView(glView, params);
    }

}