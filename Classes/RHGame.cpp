//
//  RHGame.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHGame.h"

namespace flownet
{

RHGame* RHGame::_SingletonInstance = nullptr;

RHGame::RHGame(const STRING& objectName):RHObject(objectName),
                    m_Stage()
{
}

RHGame::~RHGame()
{

}

RHGame& RHGame::Instance()
{
    if( _SingletonInstance == nullptr )
    {
        _SingletonInstance = new RHGame;
    }
    
    return *_SingletonInstance;
}

void RHGame::DeleteInstance()
{
    if( _SingletonInstance != nullptr )
    {
        delete _SingletonInstance;
    }
    _SingletonInstance = nullptr;
}

void RHGame::Initialize()
{

}

void RHGame::Tick(const float cocosDeltaTime)
{

}


} // namespace flownet