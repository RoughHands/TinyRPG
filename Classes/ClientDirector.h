//
//  ClientDirector.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__ClientDirector__
#define __TinyRPG__ClientDirector__


#include "layers_scenes_transitions_nodes/CCTransition.h"
#include "layers_scenes_transitions_nodes/CCTransitionPageTurn.h"

class ClientDirector : public cocos2d::CCDisplayLinkDirector
{
private:
    float           m_ScreenHeightAbovePlayer;
    float           m_ScreenHeightBelowPlayer;
    float           m_ScreenHeightBelowPlayerMin;
    
public:
    ClientDirector();
    virtual ~ClientDirector(){}
    
    virtual cocos2d::CCScene* getRunningScene(void);
    
    const float     GetScreenHeightAbovePlayer()    {   return m_ScreenHeightAbovePlayer; }
    const float     GetScreenHeightBelowPlayer()    {   return m_ScreenHeightBelowPlayer; }
    const float     GetScreenHeightBelowPlayerMin() {   return m_ScreenHeightBelowPlayerMin; }
    void            SetScreenHeightWithPlayer(const float above, const float below, const float below_min) { m_ScreenHeightAbovePlayer=above; m_ScreenHeightBelowPlayer=below; m_ScreenHeightBelowPlayerMin=below_min;}
    

    template<class CURRENT_SCENETYPE, class NEXT_SCENETYPE>
    bool ChangeScene()
    {
        CURRENT_SCENETYPE* scene = dynamic_cast<CURRENT_SCENETYPE*>(CCDirector::sharedDirector()->getRunningScene());
        if( scene == nullptr )
        {
            return false;
        }
        
        PauseRenderingTaskWorkerRoutine();
        
        NEXT_SCENETYPE* newScene = NEXT_SCENETYPE::create();

        scene->OnSceneChangedToDisappear();
        this->replaceScene(newScene);
        newScene->OnSceneChangedToAppear();
        
        
        //ResumeRenderingTaskWorkerRoutine();
        
        return true;
    }
    
    template<class NEXT_SCENETYPE, class TRANSITION_SCENE=cocos2d::CCTransitionFade>
    bool ChangeScene(const float transitionTime)
    {
        PauseRenderingTaskWorkerRoutine();
        
        NEXT_SCENETYPE* newScene = NEXT_SCENETYPE::create();

        BaseScene* scene = static_cast<BaseScene*>(CCDirector::sharedDirector()->getRunningScene());
        scene->OnSceneChangedToDisappear();
        //cocos2d::CCTransitionPageTurn* transitionNewScene = cocos2d::CCTransitionPageTurn::create(0.5f, newScene, false);
        TRANSITION_SCENE* transitionNewScene = TRANSITION_SCENE::create(transitionTime, newScene);
        //cocos2d::CCTransitionMoveInR* transitionNewScene = cocos2d::CCTransitionMoveInR::create(1.f, newScene);
        //cocos2d::CCTransitionSlideInR* transitionNewScene = cocos2d::CCTransitionSlideInR::create(1.f, newScene);
        //cocos2d::CCTransitionJumpZoom* transitionNewScene = cocos2d::CCTransitionJumpZoom::create(1.f, newScene);
        this->replaceScene(transitionNewScene);
        newScene->OnSceneChangedToAppear();
        
        //ResumeRenderingTaskWorkerRoutine();
        
        return true;
    }
    
    template<class TRANSITION_SCENE=cocos2d::CCTransitionFade>
    bool ChangeScene(BaseScene* newSceneWithoutRetainObject, const float transitionTime)
    {
        PauseRenderingTaskWorkerRoutine();
        
        BaseScene* scene = static_cast<BaseScene*>(CCDirector::sharedDirector()->getRunningScene());
        scene->OnSceneChangedToDisappear();
        TRANSITION_SCENE* transitionNewScene = TRANSITION_SCENE::create(transitionTime, newSceneWithoutRetainObject);
        //cocos2d::CCTransitionMoveInR* transitionNewScene = cocos2d::CCTransitionMoveInR::create(1.f, newSceneWithoutRetainObject);
        //cocos2d::CCTransitionSlideInR* transitionNewScene = cocos2d::CCTransitionSlideInR::create(1.f, newSceneWithoutRetainObject);
        //cocos2d::CCTransitionJumpZoom* transitionNewScene = cocos2d::CCTransitionJumpZoom::create(1.f, newSceneWithoutRetainObject);
        this->replaceScene(transitionNewScene);
        newSceneWithoutRetainObject->OnSceneChangedToAppear();
        
        //ResumeRenderingTaskWorkerRoutine();
        
        return true;
    }
    
    

public:
    bool IsRenderingWorkerRoutinePaused();
protected:
friend class BaseScene;
    // internal function for ChangeScene()
    void PauseRenderingTaskWorkerRoutine();
    void ResumeRenderingTaskWorkerRoutine();
};


#endif /* defined(__TinyRPG__ClientDirector__) */
