#include "AppDelegate.h"
#include "HelloWorldScene.h"

#include "BaseScene.h"
#include "GameScene.h"

#include "RHClientGame.h"

using namespace std;

USING_NS_CC;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* director = CCDirector::sharedDirector();
    CCEGLView* view = CCEGLView::sharedOpenGLView();

    director->setOpenGLView(view);
	
//    TO Do : ResolutionManager;
    
    // Spine Resolution Setting
    const CCSize currentDesignResolutionSize = designResolutionPortraitWideSize;
    view->setDesignResolutionSize(currentDesignResolutionSize.width, currentDesignResolutionSize.height, kResolutionNoBorder);
//    view->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);

	// In this demo, we select resource according to the frame's width.
	// If the resource size is different from design resolution size, you need to set contentScaleFactor.
	// We use the ratio of resource's width to the width of design resolution,
	// this can make sure that the resource's width could fit for the width of design resolution.

	vector<string> searchPath;
	CCSize frameSize = view->getFrameSize();
	if (frameSize.width > mediumResource.size.height)
    {
		// if the frame's width is larger than the width of medium resource size, select large resource.
		searchPath.push_back(largeResource.directory);
		director->setContentScaleFactor( MIN(largeResource.size.height / designResolutionSize.height, largeResource.size.width / designResolutionSize.width) );
	}
    else if (frameSize.width > smallResource.size.height)
    {
		// if the frame's width is larger than the width of small resource size, select medium resource.
		searchPath.push_back(mediumResource.directory);
		director->setContentScaleFactor( MIN(mediumResource.size.height / designResolutionSize.height, mediumResource.size.width / designResolutionSize.width) );
	}
    else
    {
		// if the frame's width is smaller than the width of medium resource size, select small resource.
		searchPath.push_back(smallResource.directory);
		director->setContentScaleFactor( MIN(smallResource.size.height / designResolutionSize.height, smallResource.size.width / designResolutionSize.width) );
	}

	searchPath.push_back("common");
    
    CCLog("[SearchPath : %s]", searchPath.front().c_str());
	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
    // End Spine Resolution Setting
    
    
    // turn on display FPS
//    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    
    
    RHClientGame::Instance().Initialize();
    
    GameScene* gameScene = GameScene::create();
    director->runWithScene(gameScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
