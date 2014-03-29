//
//  TinyRPGSharedTypes.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__TinyRPGSharedTypes__
#define __TinyRPG__TinyRPGSharedTypes__

namespace flownet
{

typedef INT64 RHActorID;
enum : INT64 {
    ActorID_None = INT64(0xffffffffffffffff),
    ActorID_ActorTypeMask = INT64(0xff00000000000000),
    ActorID_ActorTypeClearMask = INT64(0x00ffffffffffffff),
    
    ActorID_PlayerFlag = INT64(0x0000000000000000),
    ActorID_NPCFlag = INT64(0x4000000000000000),
    ActorID_MonsterFlag = INT64(0x8000000000000000),
    ActorID_StageObjectFlag = INT64(0xC000000000000000)
};

inline FBOOL IsPlayerID(const RHActorID actorID)       { return (actorID==ActorID_None)?false:((actorID&ActorID_ActorTypeMask)==ActorID_PlayerFlag); }
inline FBOOL IsNPCID(const RHActorID actorID)          { return (actorID==ActorID_None)?false:((actorID&ActorID_ActorTypeMask)==ActorID_NPCFlag); }
inline FBOOL IsMonsterID(const RHActorID actorID)      { return (actorID==ActorID_None)?false:((actorID&ActorID_ActorTypeMask)==ActorID_MonsterFlag); }
inline FBOOL IsStageObjectID(const RHActorID actorID)  { return (actorID==ActorID_None)?false:((actorID&ActorID_ActorTypeMask)==ActorID_StageObjectFlag); }

inline void SetPlayerFlag(RHActorID& actorID)         { actorID = actorID&ActorID_ActorTypeClearMask;     actorID = actorID|ActorID_PlayerFlag;}
inline void SetNPCFlag(RHActorID& actorID)            { actorID=actorID&ActorID_ActorTypeClearMask;       actorID = actorID|ActorID_NPCFlag;}
inline void SetMonsterFlag(RHActorID& actorID)        { actorID=actorID&ActorID_ActorTypeClearMask;       actorID = actorID|ActorID_MonsterFlag;}
inline void SetStageObjectFlag(RHActorID& actorID)    { actorID=actorID&ActorID_ActorTypeClearMask;       actorID = actorID|ActorID_StageObjectFlag;}

typedef Vector<RHActorID>::type RHActorIDList;


enum RHMoveDirection : INT
{
    MoveDirection_None = -1,
    MoveDirection_Left,
    MoveDirection_Right,
    MoveDirection_Center,
    MoveDirection_Max
};

enum RHActorState : INT
{
    ActorState_None = -1,
    ActorState_Idle = 0,
    ActorState_Defencing,
    ActorState_Moving,
    ActorState_Attacking,
    ActorState_Attacked,
    ActorState_Casting,
    ActorState_Max,
};



} // namespace flownet



#endif /* defined(__TinyRPG__TinyRPGSharedTypes__) */
