package com.qualcomm.QCARSamples.MultiTargets;

import java.util.ArrayList;

import android.content.Context;
import android.media.AudioManager;
import android.media.SoundPool;

public class SoundManager {

    // SoundPool is used for short sound effects
    private SoundPool mSoundPool;

    // An array of sound clip ids
    public ArrayList<Integer> mSoundIds;


    /** Initialize the sound pool and load our sound clips. */
    public SoundManager(Context context)
    {
        mSoundPool = new SoundPool(4, AudioManager.STREAM_MUSIC, 0);
        mSoundIds = new ArrayList<Integer>();

        mSoundIds.add(mSoundPool.load(context, R.raw.laser, 1));
        mSoundIds.add(mSoundPool.load(context, R.raw.bite1, 1));
        mSoundIds.add(mSoundPool.load(context, R.raw.boom, 1));
        mSoundIds.add(mSoundPool.load(context, R.raw.slurp, 1));
        mSoundIds.add(mSoundPool.load(context, R.raw.smile, 1));
        mSoundIds.add(mSoundPool.load(context, R.raw.squeeze_toy, 1));
        mSoundIds.add(mSoundPool.load(context, R.raw.toyduck, 1));
        mSoundIds.add(mSoundPool.load(context, R.raw.bullet01, 1));
        
        mSoundIds.add(mSoundPool.load(context, R.raw.coin, 1));
        mSoundIds.add(mSoundPool.load(context, R.raw.bomb, 1));
        mSoundIds.add(mSoundPool.load(context, R.raw.buying, 1));
        mSoundIds.add(mSoundPool.load(context, R.raw.nomoney, 1));
        mSoundIds.add(mSoundPool.load(context, R.raw.use, 1));
        mSoundIds.add(mSoundPool.load(context, R.raw.zombie, 1));
    }


    /** Play a sound with the given index and volume. */
    public void playSound(int soundIndex, float volume)
    {
        if (soundIndex < 0 || soundIndex >= mSoundIds.size()) {
            DebugLog.LOGE("Sound id " + soundIndex + " out of range");
            return;
        }

        mSoundPool.play(mSoundIds.get(soundIndex), volume, volume, 1, 0, 1.0f);
    }
}
