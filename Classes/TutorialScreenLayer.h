//
//  TutorialScreenLayer.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__TutorialScreenLayer__
#define __TinyRPG__TutorialScreenLayer__

class TutorialScreenLayer : public CCLayer
{
private:
    CCDrawNode*     m_TopRegion;
    CCDrawNode*     m_MidLeftRegion;
    CCDrawNode*     m_MidRightRegion;
    CCDrawNode*     m_BottomRegion;
    CCDrawNode*     m_ViewRegion;
    CCDrawNode*     m_TouchRegion;  // Center
    
    CCLabelTTF*     m_InstructionText;
    
    bool            m_IsWithPausingScene;
    
public:
    TutorialScreenLayer();
    virtual ~TutorialScreenLayer();
    
    virtual bool                        init(bool withPausingScene);
    static TutorialScreenLayer*         create(bool withPausingScene);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    
    virtual void update(float delta)    override;
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;
    
public:
    void        InitializeTouchRegion(const CCRect viewRect, const CCRect touchRect);
    void        SetInstructionText(const char* instruction);
    
};



#endif /* defined(__TinyRPG__TutorialScreenLayer__) */
