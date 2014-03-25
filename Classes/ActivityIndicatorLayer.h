//
//  ActivityIndicatorLayer.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__ActivityIndicatorLayer__
#define __TinyRPG__ActivityIndicatorLayer__

using namespace cocos2d;

class CCActivityIndicatorLayer : public CCLayer
{
private:
    bool            m_IsWithPausingScene;
    CCDrawNode*     m_Background;

public:
    CCActivityIndicatorLayer();
    virtual ~CCActivityIndicatorLayer();
    
    virtual bool                        init(bool withPausingScene);
    static CCActivityIndicatorLayer*    create(bool withPausingScene);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;
};
    


#endif /* defined(__TinyRPG__ActivityIndicatorLayer__) */
