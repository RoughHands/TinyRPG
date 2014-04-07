//
//  TinyRPGMacros.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/24/14.
//
//

#ifndef TinyRPG_TinyRPGMacros_h
#define TinyRPG_TinyRPGMacros_h

/* For demonstrating using one design resolution to match different resources,
 or one resource to match different design resolutions.

 [Situation 1] Using one design resolution to match different resources.
 Please look into Appdelegate::applicationDidFinishLaunching.
 We check current device frame size to decide which resource need to be selected.
 So if you want to test this situation which said in title '[Situation 1]',
 you should change ios simulator to different device(e.g. iphone, iphone-retina3.5, iphone-retina4.0, ipad, ipad-retina),
 or change the window size in "proj.XXX/main.cpp" by "CCEGLView::setFrameSize" if you are using win32 or linux plaform
 and modify "proj.mac/AppController.mm" by changing the window rectangle.

 [Situation 2] Using one resource to match different design resolutions.
 The coordinates in your codes is based on your current design resolution rather than resource size.
 Therefore, your design resolution could be very large and your resource size could be small.
 To test this, just define the marco 'TARGET_DESIGN_RESOLUTION_SIZE' to 'DESIGN_RESOLUTION_2048X1536'
 and open iphone simulator or create a window of 480x320 size.

 [Note] Normally, developer just need to define one design resolution(e.g. 960x640) with one or more resources.
 */

#include "cocos2d.h"

// Assert
#ifdef DEBUG
#define ASSERT_RELEASE(expression)      assert(expression)
#define ASSERT_DEBUG(expression)        assert(expression)
#else
#define ASSERT_RELEASE(expression)      {if(!(expression)){ FINT* makeCrash = nullptr; *makeCrash = MAXINT;}}
#define ASSERT_DEBUG(expression)        assert(expression)
#endif


#define DESIGN_RESOLUTION_480X320 0
#define DESIGN_RESOLUTION_960x640 1
#define DESIGN_RESOLUTION_1024X768 2
#define DESIGN_RESOLUTION_2048X1536 3

/* If you want to switch design resolution, change next line */
#define TARGET_DESIGN_RESOLUTION_SIZE DESIGN_RESOLUTION_960x640

typedef struct tagResource {
	cocos2d::CCSize size;
	char directory[100];
} Resource;

static Resource smallResource = {cocos2d::CCSizeMake(480, 320), "iphone"};
static Resource mediumResource = {cocos2d::CCSizeMake(960, 640), "iphone-retina"};
static Resource mediumWideResource = { cocos2d::CCSizeMake(1136, 640), "iphone-retina-wide" /*iphone 5 retina"*/};
static Resource largeResource = {cocos2d::CCSizeMake(1024, 768), "ipad"};
static Resource extralargeResource = {cocos2d::CCSizeMake(2048, 1536), "ipad-retina"};

#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X320)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);
static cocos2d::CCSize designResolutionWideSize = cocos2d::CCSizeMake(568, 320);
static cocos2d::CCSize designResolutionPortraitSize = cocos2d::CCSizeMake(320, 480);
static cocos2d::CCSize designResolutionPortraitWideSize = cocos2d::CCSizeMake(320, 568);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_960x640)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(960, 640);
static cocos2d::CCSize designResolutionWideSize = cocos2d::CCSizeMake(1136, 640);
static cocos2d::CCSize designResolutionPortraitSize = cocos2d::CCSizeMake(640, 960);
static cocos2d::CCSize designResolutionPortraitWideSize = cocos2d::CCSizeMake(640, 1136);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1024X768)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1024, 768);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(2048, 1536);
#else
#error unknown target design resolution!
#endif

// The font size 24 is designed for small resolution, so we should change it to fit for current design resolution
#define TITLE_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 24)


namespace cocos2d
{
    static const CCPoint CharacterAnchorPoint = ccp(0.5f, 0.f);
    static const CCPoint AnchorPointMid = ccp(0.5f, 0.5f);
    static const CCPoint AnchorPointMidTop = ccp(0.5f, 1.f);
    static const CCPoint AnchorPointMidBottom = ccp(0.5f, 0.f);
    static const CCPoint AnchorPointLeftBottom = ccp(0.f, 0.f);
    static const CCPoint AnchorPointLeftMid = ccp(0.f, 0.5f);
    static const CCPoint AnchorPointLeftTop = ccp(0.f, 1.f);
    static const CCPoint AnchorPointRightBottom = ccp(1.f, 0.f);
    static const CCPoint AnchorPointRightMid = ccp(1.f, 0.5f);
    static const CCPoint AnchorPointRightTop = ccp(1.f, 1.f);

    typedef std::function<void()> SEL_CallFuncL;

    class CC_DLL CCCallFuncL : public CCActionInstant //<NSCopying>
    {
    protected:
        SEL_CallFuncL   m_pLambda;

    public:
        CCCallFuncL(): m_pLambda(nullptr){}
        virtual ~CCCallFuncL();

        static CCCallFuncL * create(SEL_CallFuncL lambda);

        virtual bool initWithLambda(SEL_CallFuncL lambda);
        /** executes the callback */
        virtual void execute();
        //super methods
        virtual void update(float time) override;
        CCObject * copyWithZone(CCZone *pZone);
    };

    static CCRect GetRectRelatedWithAnchorPoint(CCNode* node)
    {
        CCRect rc;
        rc.origin = node->getPosition();
        rc.size = node->getContentSize();
        rc.size.width *= node->getScaleX();
        rc.size.height *= node->getScaleY();
        
        const CCPoint anchorPoint = node->getAnchorPoint();
        
        rc.origin.x = rc.origin.x-anchorPoint.x*rc.size.width;
        rc.origin.y = rc.origin.y-anchorPoint.y*rc.size.height;
        
        return rc;
    }

#define RemoveAndReleaseCCNode(NodePointer) \
    if( NodePointer != nullptr )\
    {\
        NodePointer->stopAllActions();\
        NodePointer->removeFromParent();\
        NodePointer->release();\
        NodePointer = nullptr;\
    }
}

// ScreenShot
class ScreenShotUtil
{
private:
    ScreenShotUtil(){}
public:
    ~ScreenShotUtil(){}
    
    static std::string GetScreenshotFileName();
    static bool SaveScreenshot();
    static std::string GetScreenshotFullFilePath();

};

#define TinyRPGFontName fontList[0].c_str()

#define SHOW_ANCHORPOINT_DEBUGGING


#endif
