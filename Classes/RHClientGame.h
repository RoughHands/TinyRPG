//
//  RHClientGame.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHClientGame__
#define __TinyRPG__RHClientGame__


namespace flownet
{

class RHClientGame : public RHGame
{
private:
    static RHClientGame*        _SingletonInstance;
public:
    static RHClientGame&        Instance();
    static void                 DeleteInstance();

private:
    RHActorID                   m_MyPlayerID;
    
public:
    RHClientGame(const RHGameID gameID, const RHGameType gameType, const STRING& objectName="ClientGame");
    virtual ~RHClientGame();
    
public:
    const RHActorID         GetMyPlayerID() {   return m_MyPlayerID; }
    RHPlayer*               FindMyPlayer()  { return static_cast<RHPlayer*>(this->FindActor(m_MyPlayerID)); }

    void                    UpdateMyPlayer(const milliseconds deltaTime);
    
    virtual void            Tick(const milliseconds deltaTime);
    
    void                    Initialize();
    
};

} // namespace flownet

#endif /* defined(__TinyRPG__RHClientGame__) */
