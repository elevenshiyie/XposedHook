package com.eleven.xposedhook.menu;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.eleven.xposedhook.NHook;

public class NativeSuface extends GLSurfaceView
{
    public NativeSuface(Context context) {
        super(context);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        getHolder().setFormat(PixelFormat.TRANSLUCENT);
        setZOrderOnTop(true);
        setRenderer(new CMRenderer());
    }

    class CMRenderer implements GLSurfaceView.Renderer {
        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            NHook.init();
        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            NHook.resize(width, height);
        }

        @Override
        public void onDrawFrame(GL10 gl) {
            NHook.render();
        }
    }
}