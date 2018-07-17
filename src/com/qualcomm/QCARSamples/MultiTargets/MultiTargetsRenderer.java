/*==============================================================================
            Copyright (c) 2010-2013 QUALCOMM Austria Research Center GmbH.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary

@file
    MultiTargetsRenderer.java

@brief
    Sample for MultiTargets

==============================================================================*/


package com.qualcomm.QCARSamples.MultiTargets;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;
import android.os.Message;

import com.qualcomm.QCAR.QCAR;


/** The renderer class for the MultiTargets sample. */
public class MultiTargetsRenderer implements GLSurfaceView.Renderer
{
    public boolean mIsActive = false;

    private GUIManager mGUIManager;
    private SoundManager mSoundManager;
    
    /** Native function for initializing the renderer. */
    public native void initRendering();
    
    /** Native function to update the renderer. */
    public native void updateRendering(int width, int height);

    public native void initNativeCallback();
    
    /** Called when the surface is created or recreated. */
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        DebugLog.LOGD("GLRenderer::onSurfaceCreated");

        // Call native function to initialize rendering:
        initRendering();

        // Call QCAR function to (re)initialize rendering after first use
        // or after OpenGL ES context was lost (e.g. after onPause/onResume):
        QCAR.onSurfaceCreated();
        
        initNativeCallback();
    }


    /** Called when the surface changed size. */
    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        DebugLog.LOGD("GLRenderer::onSurfaceChanged");

        // Call native function to update rendering when render surface
        // parameters have changed:
        updateRendering(width, height);

        // Call QCAR function to handle render surface size changes:
        QCAR.onSurfaceChanged(width, height);
    }


    /** The native render function. */
    public native void renderFrame();


    /** Called to draw the current frame. */
    public void onDrawFrame(GL10 gl)
    {
        if (!mIsActive)
            return;

        // Call our native function to render content:
        renderFrame();
    }
    
    public void playSoundEffect(int soundIndex, float volume)
    {
        mSoundManager.playSound(soundIndex, volume);
    }
    
    
    public void showFoodButton()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_FOOD_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }


    public void hideFoodButton()
    {
        Message message = new Message();
        message.what = GUIManager.HIDE_FOOD_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void showMainButton()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_MAIN_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }


    public void hideMainButton()
    {
        Message message = new Message();
        message.what = GUIManager.HIDE_MAIN_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void showAdvInterface()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_ADV_INTERFACE;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void hideAdvInterface()
    {
        Message message = new Message();
        message.what = GUIManager.HIDE_ADV_INTERFACE;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void showShopInterface()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_SHOP_INTERFACE;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void hideShopInterface()
    {
        Message message = new Message();
        message.what = GUIManager.HIDE_SHOP_INTERFACE;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void showUseCat()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_USE_CAT;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void showUseRabbit()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_USE_RABBIT;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void showUseBear()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_USE_BEAR;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }

    public void showSkinCat()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_SKIN_CAT;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void showSkinRabbit()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_SKIN_RABBIT;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void showSkinBear()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_SKIN_BEAR;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    
    public void showUseArrow()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_USE_ARROW;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void showUseBullet1()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_USE_BULLET1;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void showUseBullet2()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_USE_BULLET2;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void showArrow()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_ARROW;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void showBullet1()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_BULLET1;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void showBullet2()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_BULLET2;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void showShotButton()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_SHOOT_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);    	
    }
    
    public void enableBuyBerry()
    {
        Message message = new Message();
        message.what = GUIManager.BUY_BERRY;
        mGUIManager.sendThreadSafeGUIMessage(message);    	
    }

    public void enableBuyCheese()
    {
        Message message = new Message();
        message.what = GUIManager.BUY_CHEESE;
        mGUIManager.sendThreadSafeGUIMessage(message);    	
    }
    
    public void cannotBuyBerry()
    {
        Message message = new Message();
        message.what = GUIManager.CANNOT_BUY_BERRY;
        mGUIManager.sendThreadSafeGUIMessage(message);    	
    }
    
    public void cannotBuyCheese()
    {
        Message message = new Message();
        message.what = GUIManager.CANNOT_BUY_CHEESE;
        mGUIManager.sendThreadSafeGUIMessage(message);    	
    }
    
    public void displayMessage(String text)
    {
        Message message = new Message();
        message.what = GUIManager.DISPLAY_INFO_TOAST;
        message.obj = text;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void setSoundManager(SoundManager soundManager)
    {
        mSoundManager = soundManager;
    }
    
    public void setGUIManager(GUIManager guiManager)
    {
        mGUIManager = guiManager;
    }
}
