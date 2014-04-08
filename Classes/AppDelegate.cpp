#include "AppDelegate.h"
#include "HelloWorldScene.h"

#include "BaseScene.h"
#include "GameScene.h"
#include "ActorLayer.h"

#include "RHClientGame.h"

using namespace std;
using namespace flownet;
USING_NS_CC;


AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
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
    

    CCMenuItemFont::setFontSize(23);
    #ifndef GOOROOM_RELEASE_BUILD
        LogTerminal::Initialize();
        LogSystem::Initialize("GameClientSystemLog");    
        #define SET_CLIENT_LOG
        #ifndef SET_CLIENT_LOG
            LogTerminal::Instance().SetDisable(true);
            LogSystem::Instance().SetDisable(true);
        #endif // SET_CLIENT_LOG
    #else
        LogTerminal::Instance().SetDisable(true);
        LogSystem::Instance().SetDisable(true);
    #endif
    
    SplashScene* splashScene = SplashScene::create();
    director->runWithScene(splashScene);
//    GameScene* gameScene = GameScene::create();
//    director->runWithScene(gameScene);
    
    RHClientGame::Instance();
    RHGameClient& client = RHGameClient::Instance();
    
    client.InitializeClient(this);
    this->InitializeConnection();
    client.StartClient();
    

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

bool AppDelegate::InitializeConnection()
{
    RHGameClient::Instance().GetCSConnection()->InitializeClient(SERVER_CONNECT_ADDRESS, SERVER_CONNECT_PORT);
    return true;
}

void AppDelegate::RestartClient() const
{
    // Terminate
    RHGameClient::Instance().TerminateClient();

    CCDirector::sharedDirector()->stopAnimation();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    
    CCUserDefault::sharedUserDefault()->flush();
    
    // Initialize
    CCDirector::sharedDirector()->startAnimation();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    
#ifndef WITHOUT_SERVER_CONNECTION
    // Initialize GooRoomClient
    RHGameClient::Instance().InitializeClient(const_cast<AppDelegate*>(this));
//    if(!this->InitializeConnection()) CCMessageBox("Cannot connect with server", "Error!");
    const_cast<AppDelegate*>(this)->InitializeConnection();
    RHGameClient::Instance().StartClient();
#endif
    
    
    ClientDirector* clientDirector = static_cast<ClientDirector*>(CCDirector::sharedDirector());
    clientDirector->ChangeScene<SplashScene, CCTransitionFade>(0.5f);
}

void AppDelegate::ShowSystemMessage(const flownet::STRING& message) const
{
    CCMessageBox("Message", message.c_str());
}

void AppDelegate::OnCSConnected(flownet::FBOOL result, const flownet::STRING errorMessage) const
{
    if( result == false )
    {
        std::ostringstream popupMessage;
        popupMessage << "Cannot connect with server. " << std::endl << errorMessage.c_str();
        CCLOG("%s", popupMessage.str().c_str());
        return;
    }
    else
    {
        SplashScene* scene = dynamic_cast<SplashScene*>(CCDirector::sharedDirector()->getRunningScene());
        if(scene)
        {
//            scene->DisplayMessage("Connected!");
        }
        CCLOG("%s", "Success connect with GooRoomServer.\n Start the Game.");
    }
}

void AppDelegate::OnSCProtocolError() const
{
    BaseScene* scene = static_cast<BaseScene*>(CCDirector::sharedDirector()->getRunningScene());
    if(scene->GetSceneType() == SceneType_SplashScene)
    {
        SplashScene* splashScene = static_cast<SplashScene*>(scene);
        RHGameClient::Instance().GetRenderingTaskWorkerRoutine().AddTask(CreateLambdaTask("Handle Error", [this, splashScene]{
            splashScene->DisplayMessage("오류가 발생하였습니다");
        }));
    }
}


void AppDelegate::OnSCResponseConnect(flownet::ConnectionID connectionID) const
{
    CCLOG("cs connect response");
    SplashScene* scene = dynamic_cast<SplashScene*>(CCDirector::sharedDirector()->getRunningScene());
    if(scene)
    {
//        scene->DisplayMessage("Connecting ...");
    }
    
    const RHUserID userID = UserID_None; // this->LoadUserIDFromUserDefault();
    
    RHGameClient::Instance().GetCSConnection()->SendCSRequestLinkUser(userID, OTP_None);
}

void AppDelegate::OnSCResponseLinkUser(flownet::RHErrorLinkUser errorLinkUser, flownet::RHUser user) const
{
    CCLog("LinkUser : UserID[%lld], AccountName[%s]", user.GetUserID(), user.GetAccountName().c_str());

    if(errorLinkUser == ELU_Success)
    {
        RHGameClient& client = RHGameClient::Instance();
        
        client.SetUser(user);
        
//        if( user.GetGameID() != GameID_None)
//        {
//            //  Rejoin Game
////            client.Get
//            client.GetCSConnection()->SendCSRequestReJoinToUserPlayingStage(user.GetUserID(), user.GetStageID());
//            return;
//        }
//        
//        if( client.GetInvitedStageID() != StageID_None )
//        {
//            client.GetCSConnection()->SendCSRequestJoinStage(client.GetUserID(), client.GetInvitedStageID());
//            client.SetInvitedStageID(StageID_None);
//            return;
//        }
        
        SplashScene* scene = dynamic_cast<SplashScene*>(CCDirector::sharedDirector()->getRunningScene());
        if(scene)
        {
//            scene->DisplayMessage("Connected !");
            scene->DisplayTouchToGameStart();
        }
        
        // TEST Code
        client.GetCSConnection()->SendCSRequestJoinGame(client.GetUserID(), 0);
    }
    else
    {
        CCLOG("error in link user response");
        ASSERT_DEBUG(false);
    }
}

//void AppDelegate::OnFCResponseConnect(flownet::ConnectionID feConnectionID) const
//{
//    GooRoomClient& client = GooRoomClient::Instance();
//
//    // 이것은 정말로 FE의 기능을 수행하기 위한 커넥션 맺음임. 구름 클라이언트 안에 있는 커넥션인지 알 수가 없잖아...
//    if(GooRoomClient::Instance().GetCFConnection()->GetConnectionID() != feConnectionID)
//    {
//        // why just return??
//        return;
//    }
//    // below is LogIn LingUser Process ( FE -> GooRoom Server)
//
//    SplashScene* scene = dynamic_cast<SplashScene*>(CCDirector::sharedDirector()->getRunningScene());
//    if(scene)
//    {
//        scene->DisplayMessage("Connecting to KakaoTalk Server ...");
//    }
//    
////    GooRoomResourceVersionManager& resourceManager = GooRoomClient::Instance().GetGooRoomResourceVersionManager();
////    GooRoomClient::Instance().GetCFConnection()->SendCFRequestCheckVersion(0, resourceManager.GetLatestVersion());
//
//    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
//    std::stringstream kakaoIDNoneStringStream;
//    kakaoIDNoneStringStream << UserID_None;
//    std::string kakaoIDNoneString = kakaoIDNoneStringStream.str();
//
//    std::string kakaoIDString = userDefault->getStringForKey("KakaoID", kakaoIDNoneString);
//    std::stringstream kakaoIDStringStream;
//    kakaoIDStringStream << kakaoIDString;
//    KakaoID kakaoID;
//    kakaoIDStringStream >> kakaoID;
//    
//    if( kakaoID == KakaoID_None )
//    {
//        client.GetCFConnection()->SendCFTESTRequestGetMyKakaoID(0);
//    }
//    else
//    {
//        GooRoomClient::Instance().SetKakaoID(kakaoID);
//        GooRoomResourceVersionManager& resourceManager = GooRoomClient::Instance().GetGooRoomResourceVersionManager();
//        GooRoomClient::Instance().GetCFConnection()->SendCFRequestCheckVersion(0, resourceManager.GetLatestVersion());
//    }
//
//
////    switch (client.GetCFResponseConnectType()) {
////        case flownet::CFResponseConnectType_Login:
////        {
////            SplashScene* scene = dynamic_cast<SplashScene*>(CCDirector::sharedDirector()->getRunningScene());
////            if(scene)
////            {
////                scene->DisplayMessage("카카오톡 아이디를 확인중입니다");
////            }
////            
////            client.GetCFConnection().SendCFTESTRequestGetMyKakaoID(0);
////            break;
////        }
////        case flownet::CFResponseConnectType_GetPureKakaoFriendIDList :
////        {
////            client.GetCFConnection().SendCFTESTRequestGetMyKakaoFriends(client.GetKakaoID());
////            break;
////        }
////        case flownet::CFResponseConnectType_GetKakaoFriendInfoList :
////        {
////            break;
////        }
////        case flownet::CFResponseConnectType_GetGameFriendInfoList :
////        {
////            break;
////        }
////        default:
////        {
////            ASSERT_DEBUG(false);
////            break;
////        }
////    }
//}
//
//

void AppDelegate::OnSCResponseJoinGame(RHErrorJoinGame result, RHGame game, RHActorID myPlayerID) const
{
    if( result == ErrorJoinGame_Success )
    {
        RHClientGame::Instance().SetMyPlayerID(myPlayerID);
        RHClientGame::Instance().InitializeWithGame(game);
    }
    else
    {
        CCLog("Error Join Game : %d", result);
    }
    
    
}

void AppDelegate::OnSCNotifyPlayerJoin(RHGameID gameID, RHPlayer player)const
{
    if( RHClientGame::Instance().GetGameID() != gameID )
    {
        CCLog("Error GameID Wrong %lld / %lld", RHClientGame::Instance().GetGameID(), gameID);
        return;
    }
    
    RHClientGame::Instance().CreateAndAddPlayer(player);
    RHPlayer* newPlayer = RHClientGame::Instance().FindPlayer(player.GetActorID());
    
    BaseScene* baseScene = static_cast<BaseScene*>(CCDirector::sharedDirector()->getRunningScene());
    if( baseScene->GetSceneType() == SceneType_GameScene )
    {
        GameScene* gameScene = static_cast<GameScene*>(baseScene);
        gameScene->GetActorLayer()->CreateAndAddPlayerNode(newPlayer);
    }
}

RHUserID AppDelegate::LoadUserIDFromUserDefault() const
{
    // Getting UserID
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    std::stringstream userIDNoneStringStream;
    userIDNoneStringStream << UserID_None;
    std::string userIDNoneString = userIDNoneStringStream.str();

    std::string userIDString = userDefault->getStringForKey("UserID", userIDNoneString);
    std::stringstream userIDStringStream;
    userIDStringStream << userIDString;
    
    RHUserID userID;
    userIDStringStream >> userID;

    // TEST
    if(userID == UserID_None)
    {
        CCLOG("Error while getting UserID, UserID Doesn't Exist");
        // return;
    }
    
    return userID;
}

void AppDelegate::SaveUserIDToUserDefault(const RHUserID userID) const
{
    std::stringstream userIDStringStream;
    userIDStringStream << userID;
    CCUserDefault::sharedUserDefault()->setStringForKey("UserID", userIDStringStream.str());
    CCUserDefault::sharedUserDefault()->flush();
}

void AppDelegate::OnSCNotifyActorMoveWithDirection(flownet::RHGameID gameID, flownet::RHActorID actorID, flownet::RHMoveDirection moveDirection, flownet::FPOINT currentPosition) const
{
    if( gameID != RHClientGame::Instance().GetGameID() )
    {
        return;
    }
    
    RHActor* actor = RHClientGame::Instance().FindPlayer(actorID);

    if( actor->GetCurrentPosition().DistanceTo(currentPosition) >= MINIMUM_MOVE_OFFSET )
    {
        actor->SetCurrentPosition(currentPosition);
    }
    
    actor->MoveWithDirection(moveDirection);
}

void AppDelegate::OnSCNotifyActorAttackWithDirection(flownet::RHGameID gameID, flownet::RHActorID actorID, flownet::RHMoveDirection attackDirection, flownet::FPOINT currentPosition) const
{
    if( gameID != RHClientGame::Instance().GetGameID() )
    {
        return;
    }
    
    RHActor* actor = RHClientGame::Instance().FindPlayer(actorID);

    if( actor->GetCurrentPosition().DistanceTo(currentPosition) >= MINIMUM_MOVE_OFFSET )
    {
        actor->SetCurrentPosition(currentPosition);
    }
    
    // To Do : play Attack Animation only (not effect)
    actor->AttackWithDirection(attackDirection);
}
