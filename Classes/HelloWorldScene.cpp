#include "HelloWorldScene.h"
#include "spine-cocos2dx.h"

using namespace cocos2d::extension;

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
//    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
//    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
//    this->addChild(pSprite, 0);

//    CCSkeletonAnimation* skeletonNode = CCSkeletonAnimation::createWithFile("character.json", "character.atlas");
////    skeletonNode->setMix("walk", "jump", 0.2f);
////    skeletonNode->setMix("jump", "walk", 0.4f);
//    
//    skeletonNode->debugBones = true;
//    skeletonNode->update(0.f);
//    
//    skeletonNode->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1.f), CCFadeIn::create(1.f), CCDelayTime::create(5.f), nullptr)));
//    
//    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//    skeletonNode->setPosition(ccp(winSize.width*0.5f, 20.f));
//    
//    skeletonNode->setSkin("girl");
//    skeletonNode->setAnimation("idle", true);
//    
//    
//    this->addChild(skeletonNode);


    // Dragon

    CCSkeletonAnimation* skeletonNode = CCSkeletonAnimation::createWithFile("dragon.json", "dragon.atlas");
//    skeletonNode->setMix("walk", "jump", 0.2f);
//    skeletonNode->setMix("jump", "walk", 0.4f);
    
//    skeletonNode->debugBones = true;
    skeletonNode->setScale(0.5f);
    skeletonNode->update(0.f);
    
    skeletonNode->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1.f), CCFadeIn::create(1.f), CCDelayTime::create(5.f), nullptr)));
    
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    skeletonNode->setPosition(ccp(winSize.width*0.25f, winSize.height*0.3f));
    
    skeletonNode->setAnimation("flying", true);
    
    this->addChild(skeletonNode);

    // End Dragon
    
    // Boss WholeAnimating
    CCSkeletonAnimation* bossNode = CCSkeletonAnimation::createWithFile("creature_boss.json", "creature_boss.atlas");
//    bossNode->setMix("walk", "jump", 0.2f);
//    bossNode->setMix("jump", "walk", 0.4f);
    
//    bossNode->debugBones = true;
    bossNode->update(0.f);
    bossNode->setScale(0.5f);
    
    
//    bossNode->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1.f), CCFadeIn::create(1.f), CCDelayTime::create(5.f), nullptr)));
    
    bossNode->setPosition(ccp(winSize.width*0.50f, winSize.height*0.3f));
    bossNode->setAnimation("animation", true);
    this->addChild(bossNode);
    
    
    // Boss Anchor Animating
    CCSkeletonAnimation* bossAnchorNode = CCSkeletonAnimation::createWithFile("creature_boss.json", "creature_boss_hd.atlas");
//    bossAnchorNode->setMix("walk", "jump", 0.2f);
//    bossAnchorNode->setMix("jump", "walk", 0.4f);
    
    bossAnchorNode->debugBones = true;
    bossAnchorNode->update(0.f);
    bossAnchorNode->setScale(0.5f);
    
//    bossAnchorNode->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1.f), CCFadeIn::create(1.f), CCDelayTime::create(5.f), nullptr)));
    
    
    CCPoint bossPosition = ccp(winSize.width*0.80f, winSize.height*0.3f);
    bossAnchorNode->setPosition(bossPosition);
    bossAnchorNode->setAnchorPoint(AnchorPointMid);
    float* scale = new float(0.5f);
    CCCallFuncL* jumpAnimating = CCCallFuncL::create([bossAnchorNode, scale]()
    {
        bossAnchorNode->addAnimation("anticipate", false, 0);
        bossAnchorNode->addAnimation("jump", false, 0);
        bossAnchorNode->addAnimation("in air", false, 0);
        bossAnchorNode->addAnimation("fall", false, 0);
        bossAnchorNode->addAnimation("recover", false, 0);
//        bossAnchorNode->skeleton->flipX = !bossAnchorNode->skeleton->flipX;
        
        *scale = -(*scale);
        bossAnchorNode->setScaleX(*scale);
//        bossAnchorNode->updateWorldTransform(!bossAnchorNode->skeleton->flipX);
    });
    
    bossAnchorNode->runAction(CCRepeatForever::create(CCSequence::create(jumpAnimating, CCDelayTime::create(3.5f), nullptr)));
    
    CCCallFuncL* bossAnchorUpdate =  CCCallFuncL::create([bossAnchorNode, bossPosition]()
    {
        Bone* rootBone = bossAnchorNode->findBone("root");
        CCPoint rootBonePosition = ccp(rootBone->x , rootBone->y);
        CCLog("RootBone [%f, %f]", rootBonePosition.x, rootBonePosition.y);
        CCLog("BossPosition [%f, %f]", bossAnchorNode->getPositionX(), bossAnchorNode->getPositionY());
    });
    
    bossAnchorNode->runAction(CCRepeatForever::create(CCSpawn::create(bossAnchorUpdate,nullptr)));
    
    
    this->addChild(bossAnchorNode);
    // End Boss Anchor Animating

    
    this->scheduleUpdate();
    
    
    // Spine Test
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
