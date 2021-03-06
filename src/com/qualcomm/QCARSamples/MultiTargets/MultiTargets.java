/*==============================================================================
            Copyright (c) 2010-2013 QUALCOMM Austria Research Center GmbH.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary

@file
    MultiTargets.java

@brief
    Sample for MultiTargets

==============================================================================*/


package com.qualcomm.QCARSamples.MultiTargets;

import java.util.Vector;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.util.DisplayMetrics;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.ImageView;
import android.widget.Toast;

import com.qualcomm.QCAR.QCAR;

/** The main activity for the MultiTargets sample. */
public class MultiTargets extends Activity
{
    // Menu item string constants:
    private static final String MENU_ITEM_ACTIVATE_CONT_AUTO_FOCUS =
        "Activate Cont. Auto focus";
    private static final String MENU_ITEM_DEACTIVATE_CONT_AUTO_FOCUS =
        "Deactivate Cont. Auto focus";

    // Focus mode constants:
    private static final int FOCUS_MODE_NORMAL = 0;
    private static final int FOCUS_MODE_CONTINUOUS_AUTO = 1;

    // Application status constants:
    private static final int APPSTATUS_UNINITED         = -1;
    private static final int APPSTATUS_INIT_APP         = 0;
    private static final int APPSTATUS_INIT_QCAR        = 1;
    private static final int APPSTATUS_INIT_TRACKER     = 2;
    private static final int APPSTATUS_INIT_APP_AR      = 3;
    private static final int APPSTATUS_LOAD_TRACKER     = 4;
    private static final int APPSTATUS_INITED           = 5;
    private static final int APPSTATUS_CAMERA_STOPPED   = 6;
    private static final int APPSTATUS_CAMERA_RUNNING   = 7;

    // Name of the native dynamic libraries to load:
    private static final String NATIVE_LIB_SAMPLE = "MultiTargets";
    private static final String NATIVE_LIB_QCAR = "QCAR";

    // Our OpenGL view:
    private QCARSampleGLView mGlView;

    // The view to display the sample splash screen:
    private ImageView mSplashScreenView;

    // The handler and runnable for the splash screen time out task:
    private Handler mSplashScreenHandler;
    private Runnable mSplashScreenRunnable;

    // The minimum time the splash screen should be visible:
    private static final long MIN_SPLASH_SCREEN_TIME = 2000;

    // The time when the splash screen has become visible:
    long mSplashScreenStartTime = 0;

    // Our renderer:
    private MultiTargetsRenderer mRenderer;

    // Display size of the device:
    private int mScreenWidth = 0;
    private int mScreenHeight = 0;

    // The current application status:
    private int mAppStatus = APPSTATUS_UNINITED;

    // The async tasks to initialize the QCAR SDK :
    private InitQCARTask mInitQCARTask;
    private LoadTrackerTask mLoadTrackerTask;

    // An object used for synchronizing QCAR initialization, dataset loading and
    // the Android onDestroy() life cycle event. If the application is destroyed
    // while a data set is still being loaded, then we wait for the loading
    // operation to finish before shutting down QCAR.
    private Object mShutdownLock = new Object();

    // QCAR initialization flags:
    private int mQCARFlags = 0;

    // The textures we will use for rendering:
    private Vector<Texture> mTextures;
    private int mSplashScreenImageResource = 0;

    // GUI managers
    private SoundManager mSoundManager;
    private GUIManager mGUIManager;
    
    // The current focus mode selected:
    private int mFocusMode;
    
    // variable for reading data
    private int money_ReadData = 0;
    private int score_ReadData = 0;
    private int BP_ReadData = 50;
    private boolean cat_ReadData = false;
    private boolean bear_ReadData = false;
    private int pet_Type = 0;
    private int berry_ReadData = 3;
    private int cheese_ReadData = 3;
    private boolean bullet1_ReadData = false;
    private boolean bullet2_ReadData = false;
    private int armType_ReadData = 53;

    /** Static initializer block to load native libraries on start-up. */
    static
    {
        loadLibrary(NATIVE_LIB_QCAR);
        loadLibrary(NATIVE_LIB_SAMPLE);
    }

    /** An async task to initialize QCAR asynchronously. */
    private class InitQCARTask extends AsyncTask<Void, Integer, Boolean>
    {
        // Initialize with invalid value:
        private int mProgressValue = -1;

        protected Boolean doInBackground(Void... params)
        {
            // Prevent the onDestroy() method to overlap with initialization:
            synchronized (mShutdownLock)
            {
                QCAR.setInitParameters(MultiTargets.this, mQCARFlags);

                do
                {
                    // QCAR.init() blocks until an initialization step is
                    // complete, then it proceeds to the next step and reports
                    // progress in percents (0 ... 100%)
                    // If QCAR.init() returns -1, it indicates an error.
                    // Initialization is done when progress has reached 100%.
                    mProgressValue = QCAR.init();

                    // Publish the progress value:
                    publishProgress(mProgressValue);

                    // We check whether the task has been canceled in the
                    // meantime (by calling AsyncTask.cancel(true))
                    // and bail out if it has, thus stopping this thread.
                    // This is necessary as the AsyncTask will run to completion
                    // regardless of the status of the component that
                    // started is.
                } while (!isCancelled() && mProgressValue >= 0
                         && mProgressValue < 100);

                return (mProgressValue > 0);
            }
        }


        protected void onProgressUpdate(Integer... values)
        {
            // Do something with the progress value "values[0]", e.g. update
            // splash screen, progress bar, etc.
        }


        protected void onPostExecute(Boolean result)
        {
            // Done initializing QCAR, proceed to next application
            // initialization status:
            if (result)
            {
                DebugLog.LOGD("InitQCARTask::onPostExecute: QCAR " +
                              "initialization successful");

                updateApplicationStatus(APPSTATUS_INIT_TRACKER);
            }
            else
            {
                // Create dialog box for display error:
                AlertDialog dialogError = new AlertDialog.Builder
                (
                    MultiTargets.this
                ).create();

                dialogError.setButton
                (
                    DialogInterface.BUTTON_POSITIVE,
                    "Close",
                    new DialogInterface.OnClickListener()
                    {
                        public void onClick(DialogInterface dialog, int which)
                        {
                            // Exiting application
                            System.exit(1);
                        }
                    }
                );

                String logMessage;

                // NOTE: Check if initialization failed because the device is
                // not supported. At this point the user should be informed
                // with a message.
                if (mProgressValue == QCAR.INIT_DEVICE_NOT_SUPPORTED)
                {
                    logMessage = "Failed to initialize QCAR because this " +
                        "device is not supported.";
                }
                else
                {
                    logMessage = "Failed to initialize QCAR.";
                }

                // Log error:
                DebugLog.LOGE("InitQCARTask::onPostExecute: " + logMessage +
                                " Exiting.");

                // Show dialog box with error message:
                dialogError.setMessage(logMessage);
                dialogError.show();
            }
        }
    }


    /** An async task to load the tracker data asynchronously. */
    private class LoadTrackerTask extends AsyncTask<Void, Integer, Boolean>
    {
        protected Boolean doInBackground(Void... params)
        {
            // Prevent the onDestroy() method to overlap:
            synchronized (mShutdownLock)
            {
                // Load the tracker data set:
                return (loadTrackerData() > 0);
            }
        }

        protected void onPostExecute(Boolean result)
        {
            DebugLog.LOGD("LoadTrackerTask::onPostExecute: execution " +
                        (result ? "successful" : "failed"));

            if (result)
            {
                // Done loading the tracker, update application status:
                updateApplicationStatus(APPSTATUS_INITED);
            }
            else
            {
                // Create dialog box for display error:
                AlertDialog dialogError = new AlertDialog.Builder
                (
                    MultiTargets.this
                ).create();

                dialogError.setButton
                (
                    DialogInterface.BUTTON_POSITIVE,
                    "Close",
                    new DialogInterface.OnClickListener()
                    {
                        public void onClick(DialogInterface dialog, int which)
                        {
                            // Exiting application:
                            System.exit(1);
                        }
                    }
                );

                // Show dialog box with error message:
                dialogError.setMessage("Failed to load tracker data.");
                dialogError.show();
            }
        }
    }


    private void storeScreenDimensions()
    {
        // Query display dimensions:
        DisplayMetrics metrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(metrics);
        mScreenWidth = metrics.widthPixels;
        mScreenHeight = metrics.heightPixels;
    }
    
    /** Called when the activity first starts or the user navigates back
     * to an activity. */
    protected void onCreate(Bundle savedInstanceState)
    {
        DebugLog.LOGD("MultiTargets::onCreate");
        super.onCreate(savedInstanceState);
                
     	SharedPreferences data_storage = getSharedPreferences("dataFile", MODE_PRIVATE);
    	money_ReadData = data_storage.getInt("money", 0);
    	score_ReadData = data_storage.getInt("score", 0);
    	BP_ReadData    = data_storage.getInt("BP", 50);
    	cat_ReadData   = data_storage.getBoolean("cat", false);
    	bear_ReadData  = data_storage.getBoolean("bear", false);  
    	pet_Type       = data_storage.getInt("skin", 0);  
    	berry_ReadData = data_storage.getInt("berry", 3);
    	cheese_ReadData = data_storage.getInt("cheese", 3);
    	bullet1_ReadData = data_storage.getBoolean("bullet1", false); 
    	bullet2_ReadData = data_storage.getBoolean("bullet2", false); 
    	armType_ReadData = data_storage.getInt("arm", 53);
    	
        // Set the splash screen image to display during initialization:
        mSplashScreenImageResource = R.drawable.vuf_vrt_rev;

        // Load any sample specific textures:
        mTextures = new Vector<Texture>();
        loadTextures();

        // Query the QCAR initialization flags:
        mQCARFlags = getInitializationFlags();

        // Update the application status to start initializing application:
        updateApplicationStatus(APPSTATUS_INIT_APP);
    }


    /** We want to load specific textures from the APK, which we will later
    use for rendering. */
    private void loadTextures()
    {
        mTextures.add(Texture.loadTextureFromApk("texturepet3.png",
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("CheeseCake.jpg",
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("texturepet3_eat.png",
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("strawberry.jpg",
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("Tachas.jpg", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("Gold_Texture.jpg", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("texturepet3_eat.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("texturepet3_cry.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("shop_background.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("game_hp.png", 
                getAssets()));      
        mTextures.add(Texture.loadTextureFromApk("bat_fly2.png", 
                getAssets()));   
        mTextures.add(Texture.loadTextureFromApk("arm_lv1.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("texturepet4.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("texturepet4_eat.png",
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("texturepet4_eat.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("texturepet4_cry.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("texturepet5.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("texturepet5_eat.png",
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("texturepet5_eat.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("texturepet5_cry.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("monster_die_unit.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("number_white_0.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("number_white_1.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("number_white_2.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("number_white_3.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("number_white_4.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("number_white_5.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("number_white_6.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("number_white_7.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("number_white_8.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("number_white_9.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("score.png", 
                getAssets()));
        mTextures.add(Texture.loadTextureFromApk("texturepet3_die.png", 
                getAssets())); 
        mTextures.add(Texture.loadTextureFromApk("texturepet4_die.png", 
                getAssets())); 
        mTextures.add(Texture.loadTextureFromApk("texturepet5_die.png", 
                getAssets())); 
        mTextures.add(Texture.loadTextureFromApk("bat_fly1.png", 
                getAssets()));   
        mTextures.add(Texture.loadTextureFromApk("bat_fly3.png", 
                getAssets()));   
        mTextures.add(Texture.loadTextureFromApk("mp_bar.png", 
                getAssets()));   
        mTextures.add(Texture.loadTextureFromApk("mp_bar_frame.png", 
                getAssets())); 
    	mTextures.add(Texture.loadTextureFromApk("crystal_blue.png",
                getAssets()));
    	mTextures.add(Texture.loadTextureFromApk("crystal_purple.png",
                getAssets()));
    	mTextures.add(Texture.loadTextureFromApk("dragon_fly1.png",
                getAssets()));
    	mTextures.add(Texture.loadTextureFromApk("dragon_fly2.png",
                getAssets()));
    	mTextures.add(Texture.loadTextureFromApk("dragon_fly3.png",
                getAssets()));
    	mTextures.add(Texture.loadTextureFromApk("money.png",
                getAssets()));
    	mTextures.add(Texture.loadTextureFromApk("lightBall2.png",
                getAssets()));
    	mTextures.add(Texture.loadTextureFromApk("sight_v3.png",
                getAssets()));   	   	
    	mTextures.add(Texture.loadTextureFromApk("zombie_move1.png",
                getAssets()));
    	mTextures.add(Texture.loadTextureFromApk("chat_1.png",
                getAssets()));   	
    	mTextures.add(Texture.loadTextureFromApk("chat_2.png",
                getAssets()));   
    	mTextures.add(Texture.loadTextureFromApk("chat_3.png",
                getAssets()));  
    	mTextures.add(Texture.loadTextureFromApk("arm_lv2.png",
                getAssets()));       
    	mTextures.add(Texture.loadTextureFromApk("arm_lv3.png",
                getAssets()));   
    	mTextures.add(Texture.loadTextureFromApk("arm_arrow.png",
                getAssets()));   
    	mTextures.add(Texture.loadTextureFromApk("BestScore.png",
                getAssets()));   
    	mTextures.add(Texture.loadTextureFromApk("Gold_coin_icon.png",
                getAssets()));   
    	mTextures.add(Texture.loadTextureFromApk("multiply_sign.png",
                getAssets()));  
    	mTextures.add(Texture.loadTextureFromApk("chat_4.png",
                getAssets())); 
    }


    /** Configure QCAR with the desired version of OpenGL ES. */
    private int getInitializationFlags()
    {
        return QCAR.GL_20;
    }


    /** Native tracker initialization and deinitialization. */
    public native int initTracker();
    public native void deinitTracker();

    /** Native functions to load and destroy tracking data. */
    public native int loadTrackerData();
    public native void destroyTrackerData();


    /** Native methods for starting and stopping the camera. */
    private native void startCamera();
    private native void stopCamera();

    /** Native method for setting / updating the projection matrix for
     * AR content rendering */
    private native void setProjectionMatrix();

    /** Native sample initialization. */
    public native void onQCARInitializedNative();


   /** Called when the activity will start interacting with the user.*/
    protected void onResume()
    {
        DebugLog.LOGD("MultiTargets::onResume");
        super.onResume();

        // QCAR-specific resume operation:
        QCAR.onResume();

        // We may start the camera only if the QCAR SDK has already been
        // initialized:
        if (mAppStatus == APPSTATUS_CAMERA_STOPPED)
        {
            updateApplicationStatus(APPSTATUS_CAMERA_RUNNING);
        }

        // Resume the GL view:
        if (mGlView != null)
        {
            mGlView.setVisibility(View.VISIBLE);
            mGlView.onResume();
        }
        
        if (mGUIManager != null)
        {
            mGUIManager.initButtons();
        }
    }

    public void onConfigurationChanged(Configuration config)
    {
        DebugLog.LOGD("MultiTargets::onConfigurationChanged");
        super.onConfigurationChanged(config);

        storeScreenDimensions();

        // Set projection matrix:
        if (QCAR.isInitialized() && (mAppStatus == APPSTATUS_CAMERA_RUNNING))
            setProjectionMatrix();
    }


    public native void dataEditor();
    
    private int money_SaveData = 0;
    private int score_SaveData = 0;
    private int BP_SaveData = 0;
    private boolean cat_SaveData = false;
    private boolean bear_SaveData = false;  
    private int skin_SaveData = 0;
    private int berry_SaveData = 0;
    private int cheese_SaveData = 0;
    private boolean bullet1_SaveData = false;
    private boolean bullet2_SaveData = false;
    private int armType_SaveData = 53;
    
	public void transmitData(int money, int score, int bp, boolean catSkin, boolean bearSkin, 
			                 int petType, int berryHold, int cheeseHold, boolean bullet1, boolean bullet2, int armType){
		money_SaveData = money;
		score_SaveData = score;
		BP_SaveData = bp;
		cat_SaveData = catSkin;
		bear_SaveData = bearSkin;
		skin_SaveData = petType;
		berry_SaveData = berryHold;
		cheese_SaveData = cheeseHold;
		bullet1_SaveData = bullet1; 
		bullet2_SaveData = bullet2;
		armType_SaveData = armType;
	}
	

    /** Called when the system is about to start resuming a previous activity.*/
    protected void onPause()
    {
        DebugLog.LOGD("MultiTargets::onPause");
        super.onPause();

    	// use dataEditor in cpp
        // creat jni of SharedPreferences    
        
        dataEditor();
        
     	SharedPreferences data_storage = getSharedPreferences("dataFile", MODE_PRIVATE);
     	SharedPreferences.Editor editor = data_storage.edit();
    	editor.putInt("money", money_SaveData);
    	editor.putInt("score", score_SaveData);
    	editor.putInt("BP", BP_SaveData);
    	editor.putBoolean("cat", cat_SaveData);
    	editor.putBoolean("bear", bear_SaveData);
    	editor.putInt("skin", skin_SaveData);
    	editor.putInt("berry", berry_SaveData);
    	editor.putInt("cheese", cheese_SaveData);
    	editor.putBoolean("bullet1", bullet1_SaveData);
    	editor.putBoolean("bullet2", bullet2_SaveData);
    	editor.putInt("arm", armType_SaveData);
    	
    	editor.commit();
        
        if (mGlView != null)
        {
            mGlView.setVisibility(View.INVISIBLE);
            mGlView.onPause();
        }
        
        if (mGUIManager != null)
        {
            mGUIManager.deinitButtons();
            //mGUIManager.nativeReset();
        }

        if (mAppStatus == APPSTATUS_CAMERA_RUNNING)
        {
            updateApplicationStatus(APPSTATUS_CAMERA_STOPPED);
        }

        // QCAR-specific pause operation:
        QCAR.onPause();
    }


    /** Native function to deinitialize the application.*/
    private native void deinitApplicationNative();


    /** The final call you receive before your activity is destroyed.*/
    protected void onDestroy()
    {
        DebugLog.LOGD("MultiTargets::onDestroy");
        super.onDestroy();

        // Dismiss the splash screen time out handler:
        if (mSplashScreenHandler != null)
        {
            mSplashScreenHandler.removeCallbacks(mSplashScreenRunnable);
            mSplashScreenRunnable = null;
            mSplashScreenHandler = null;
        }

        // Cancel potentially running tasks:
        if (mInitQCARTask != null &&
            mInitQCARTask.getStatus() != InitQCARTask.Status.FINISHED)
        {
            mInitQCARTask.cancel(true);
            mInitQCARTask = null;
        }

        if (mLoadTrackerTask != null &&
            mLoadTrackerTask.getStatus() != LoadTrackerTask.Status.FINISHED)
        {
            mLoadTrackerTask.cancel(true);
            mLoadTrackerTask = null;
        }

        // Ensure that all asynchronous operations to initialize QCAR and loading
        // the tracker datasets do not overlap:
        synchronized (mShutdownLock) {

            // Do application deinitialization in native code:
            deinitApplicationNative();

            // Unload texture:
            mTextures.clear();
            mTextures = null;

            // Destroy the tracking data set:
            destroyTrackerData();

            // Deinit the tracker:
            deinitTracker();

            // Deinitialize QCAR SDK
            QCAR.deinit();
        }

        System.gc();
    }


    /** NOTE: this method is synchronized because of a potential concurrent
     * access by MultiTargets::onResume() and InitQCARTask::onPostExecute(). */
    private synchronized void updateApplicationStatus(int appStatus)
    {
        // Exit if there is no change in status:
        if (mAppStatus == appStatus)
            return;

        // Store new status value:
        mAppStatus = appStatus;

        // Execute application state-specific actions:
        switch (mAppStatus)
        {
            case APPSTATUS_INIT_APP:
                // Initialize application elements that do not rely on QCAR
                // initialization:
                initApplication();

                // Proceed to next application initialization status:
                updateApplicationStatus(APPSTATUS_INIT_QCAR);
                break;

            case APPSTATUS_INIT_QCAR:
                // Initialize QCAR SDK asynchronously to avoid blocking the
                // main (UI) thread.
                //
                // NOTE: This task instance must be created and invoked on the
                // UI thread and it can be executed only once!
                try
                {
                    mInitQCARTask = new InitQCARTask();
                    mInitQCARTask.execute();
                }
                catch (Exception e)
                {
                    DebugLog.LOGE("Initializing QCAR SDK failed");
                }
                break;

            case APPSTATUS_INIT_TRACKER:
                // Initialize the ImageTracker:
                if (initTracker() > 0)
                {
                    // Proceed to next application initialization status:
                    updateApplicationStatus(APPSTATUS_INIT_APP_AR);
                }
                break;

            case APPSTATUS_INIT_APP_AR:
                // Initialize Augmented Reality-specific application elements
                // that may rely on the fact that the QCAR SDK has been
                // already initialized:
                initApplicationAR();

                // Proceed to next application initialization status:
                updateApplicationStatus(APPSTATUS_LOAD_TRACKER);
                break;

            case APPSTATUS_LOAD_TRACKER:
                // Load the tracking data set:
                //
                // NOTE: This task instance must be created and invoked on the
                // UI thread and it can be executed only once!
                try
                {
                    mLoadTrackerTask = new LoadTrackerTask();
                    mLoadTrackerTask.execute();
                }
                catch (Exception e)
                {
                    DebugLog.LOGE("Loading tracking data set failed");
                }
                break;

            case APPSTATUS_INITED:
                // Hint to the virtual machine that it would be a good time to
                // run the garbage collector.
                //
                // NOTE: This is only a hint. There is no guarantee that the
                // garbage collector will actually be run.
                System.gc();

                onQCARInitializedNative();

                // The elapsed time since the splash screen was visible:
                long splashScreenTime = System.currentTimeMillis() -
                                            mSplashScreenStartTime;
                long newSplashScreenTime = 0;
                if (splashScreenTime < MIN_SPLASH_SCREEN_TIME)
                {
                    newSplashScreenTime = MIN_SPLASH_SCREEN_TIME -
                                            splashScreenTime;
                }

                // Request a callback function after a given timeout to dismiss
                // the splash screen:
                mSplashScreenHandler = new Handler();
                mSplashScreenRunnable =
                    new Runnable() {
                        public void run()
                        {
                            // Hide the splash screen:
                            mSplashScreenView.setVisibility(View.INVISIBLE);

                            // Activate the renderer:
                            mRenderer.mIsActive = true;

                            // Now add the GL surface view. It is important
                            // that the OpenGL ES surface view gets added
                            // BEFORE the camera is started and video
                            // background is configured.
                            addContentView(mGlView, new LayoutParams(
                                            LayoutParams.MATCH_PARENT,
                                            LayoutParams.MATCH_PARENT));
                            
                            addContentView(mGUIManager.getOverlayView(),
                            				new LayoutParams(
                            				LayoutParams.MATCH_PARENT,
                            				LayoutParams.MATCH_PARENT));

                            mGUIManager.initButtons();

                            // Start the camera:
                            updateApplicationStatus(APPSTATUS_CAMERA_RUNNING);
                        }
                };

                mSplashScreenHandler.postDelayed(mSplashScreenRunnable,
                                                    newSplashScreenTime);
                break;

            case APPSTATUS_CAMERA_STOPPED:
                // Call the native function to stop the camera:
                stopCamera();
                break;

            case APPSTATUS_CAMERA_RUNNING:
                // Call the native function to start the camera:
                startCamera();
                setProjectionMatrix();

                // Set continuous auto-focus if supported by the device,
                // otherwise default back to regular auto-focus mode.
                // This will be activated by a tap to the screen in this
                // application.
                mFocusMode = FOCUS_MODE_CONTINUOUS_AUTO;
                if(!setFocusMode(mFocusMode))
                {
                    mFocusMode = FOCUS_MODE_NORMAL;
                    setFocusMode(mFocusMode);
                }

                break;

            default:
                throw new RuntimeException("Invalid application state");
        }
    }


    /** Tells native code whether we are in portait or landscape mode */
    private native void setActivityPortraitMode(boolean isPortrait);


    /** Initialize application GUI elements that are not related to AR. */
    private void initApplication()
    {
        // Set the screen orientation:
        int screenOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;

        // Apply screen orientation:
        setRequestedOrientation(screenOrientation);

        // Pass on screen orientation info to native code:
        setActivityPortraitMode(
            screenOrientation == ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

        storeScreenDimensions();

        // As long as this window is visible to the user, keep the device's
        // screen turned on and bright:
        getWindow().setFlags(
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON,
            WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        // Create and add the splash screen view:
        mSplashScreenView = new ImageView(this);
        mSplashScreenView.setImageResource(mSplashScreenImageResource);
        addContentView(mSplashScreenView, new LayoutParams(
                        LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));

        mSplashScreenStartTime = System.currentTimeMillis();

    }


    /** Native function to initialize the application. */
    private native void initApplicationNative(int width, int height);


    /** Initializes AR application components. */
    private void initApplicationAR()
    {
        // Do application initialization in native code (e.g. registering
        // callbacks, etc.):
        initApplicationNative(mScreenWidth, mScreenHeight);

        // Create OpenGL ES view:
        int depthSize = 16;
        int stencilSize = 0;
        boolean translucent = QCAR.requiresAlpha();

        mGlView = new QCARSampleGLView(this);
        mGlView.init(mQCARFlags, translucent, depthSize, stencilSize);

        mRenderer = new MultiTargetsRenderer();
        mGlView.setRenderer(mRenderer);
        
        mSoundManager = new SoundManager(getApplicationContext());
        mRenderer.setSoundManager(mSoundManager);
        
        mGUIManager = new GUIManager(getApplicationContext());
        mRenderer.setGUIManager(mGUIManager);

        mGlView.setOnClickListener(new OnClickListener(){
            public void onClick(View v) {
                autofocus();
                
                // Autofocus action resets focus mode
                mFocusMode = FOCUS_MODE_NORMAL;
            }});

    }

    /** Invoked every time before the options menu gets displayed to give
     *  the Activity a chance to populate its Menu with menu items. */
    public boolean onPrepareOptionsMenu(Menu menu) 
    {
        super.onPrepareOptionsMenu(menu);
        
        menu.clear();

        if(mFocusMode == FOCUS_MODE_CONTINUOUS_AUTO)
            menu.add(MENU_ITEM_DEACTIVATE_CONT_AUTO_FOCUS);
        else
            menu.add(MENU_ITEM_ACTIVATE_CONT_AUTO_FOCUS);

        return true;
    }

    /** Invoked when the user selects an item from the Menu */
    public boolean onOptionsItemSelected(MenuItem item)
    {
        if(item.getTitle().equals(MENU_ITEM_ACTIVATE_CONT_AUTO_FOCUS))
        {
            if(setFocusMode(FOCUS_MODE_CONTINUOUS_AUTO))
            {
                mFocusMode = FOCUS_MODE_CONTINUOUS_AUTO;
                item.setTitle(MENU_ITEM_DEACTIVATE_CONT_AUTO_FOCUS);
            }
            else
            {
                Toast.makeText
                (
                    this,
                    "Unable to activate Continuous Auto-Focus",
                    Toast.LENGTH_SHORT
                ).show();
            }
        }
        else if(item.getTitle().equals(MENU_ITEM_DEACTIVATE_CONT_AUTO_FOCUS))
        {
            if(setFocusMode(FOCUS_MODE_NORMAL))
            {
                mFocusMode = FOCUS_MODE_NORMAL;
                item.setTitle(MENU_ITEM_ACTIVATE_CONT_AUTO_FOCUS);
            }
            else
            {
                Toast.makeText
                (
                    this,
                    "Unable to deactivate Continuous Auto-Focus",
                    Toast.LENGTH_SHORT
                ).show();
            }
        }

        return true;
    }

    private native boolean autofocus();
    private native boolean setFocusMode(int mode);

    
    // function to load the save data
    public int getBpData(){
        return BP_ReadData;
    }    
    public int getScoreData(){
        return score_ReadData;
    }
    public int getMoneyData(){
        return money_ReadData;
    }
    public boolean getBearData(){
        return bear_ReadData;
    }
    public boolean getCatData(){
        return cat_ReadData;
    }
    public int getSkinData(){
        return pet_Type;
    }
    public int getBerryData(){
    	return berry_ReadData;
    }
    public int getCheeseData(){
    	return cheese_ReadData;
    }
    public boolean getBullet1Data(){
        return bullet1_ReadData;
    }
    public boolean getBullet2Data(){
        return bullet2_ReadData;
    }
    public int getArmTypeData(){
    	return armType_ReadData;
    }
    
    
    /** Returns the number of registered textures. */
    public int getTextureCount()
    {
        return mTextures.size();
    }


    /** Returns the texture object at the specified index. */
    public Texture getTexture(int i)
    {
        return mTextures.elementAt(i);
    }


    /** A helper for loading native libraries stored in "libs/armeabi*". */
    public static boolean loadLibrary(String nLibName)
    {
        try
        {
            System.loadLibrary(nLibName);
            DebugLog.LOGI("Native library lib" + nLibName + ".so loaded");
            return true;
        }
        catch (UnsatisfiedLinkError ulee)
        {
            DebugLog.LOGE("The library lib" + nLibName +
                            ".so could not be loaded");
        }
        catch (SecurityException se)
        {
            DebugLog.LOGE("The library lib" + nLibName +
                            ".so was not allowed to be loaded");
        }

        return false;
    }
}
