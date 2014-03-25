//
//  AudioEngine.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__AudioEngine__
#define __TinyRPG__AudioEngine__

#include "SimpleAudioEngine.h"

class AudioEngine
{
public:
    enum {
        MUTE = 0xFEEDBAB,
    };

    static AudioEngine* Instance();
    static void Destory();

private:
    static AudioEngine* instance;
    
    AudioEngine();
    ~AudioEngine();

    CocosDenshion::SimpleAudioEngine* m_Engine;
    std::string m_CurrentBackgroundMusic;
  
public:
    void SetBackgroundVolume(float volume);
    float GetBackgroundVolume();
    
    void SetEffectVolume(float volume);
    float GetEffectVolume();

    void PlayBackgroundMusic(std::string fileName, bool loop);
    void PlayBackgroundMusic(std::string fileName);
    void StopBackgroundMusic(bool release);
    void StopBackgroundMusic();
    void PauseBackgroundMusic();
    void ResumeBackgroundMusic();
    
    unsigned int PlayEffect(std::string fileName, bool loop);
    unsigned int PlayEffect(std::string fileName);
    void StopAllEffects();
    void StopEffect(unsigned int effectID);
    void PauseAllEffects();
    void ResumeAllEffects();
    
    void Vibrate(long long time);
};


#endif /* defined(__TinyRPG__AudioEngine__) */
