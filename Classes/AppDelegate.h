#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

#include "TinyRPGMacros.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  AppDelegate : private cocos2d::CCApplication, flownet::TinyRPGClientRPCInterface
{
public:
    AppDelegate();
    virtual ~AppDelegate();
    
    // Test

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
    

    bool            InitializeConnection();
    
    virtual void    RestartClient() const override;
    virtual void    ShowSystemMessage(const flownet::STRING& message) const override;
    virtual void    OnCSConnected(flownet::FBOOL result, const flownet::STRING errorMessage) const override;

    #include "TinyRPGSCOverrideProtocolHandlerDeclaration.hpp"
};

#endif // _APP_DELEGATE_H_

