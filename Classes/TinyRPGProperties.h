//
//  TinyRPGProperties.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__TinyRPGProperties__
#define __TinyRPG__TinyRPGProperties__

// system
#define THREAD_SCHEDULING_TIMESLICE         30                  //milliseconds

// server connection
//#define SERVER_CONNECT_ADDRESS          "172.16.100.66"
#define SERVER_CONNECT_ADDRESS           "121.162.245.90"       //SW Maestro Center
//#define SERVER_CONNECT_ADDRESS           "61.43.139.21"       //SW Maestro Center
#define SERVER_CONNECT_PORT              1788

//#define FESERVER_CONNECT_ADDRESS        "172.16.100.66"
#define FESERVER_CONNECT_ADDRESS        "121.162.245.90"
//#define FESERVER_CONNECT_ADDRESS        "61.43.139.21"
#define FESERVER_CONNECT_PORT           2967


#define MOVE_RESOLUTION 1.5f
#define MINIMUM_MOVE_OFFSET 50.f

static const float VIEW_SIZE_WIDTH = 640.f;
static const float VIEW_SIZE_HEIGHT = 640.f;

static const float VIEW_LEFT_BOUND = VIEW_SIZE_WIDTH*0.25f;
static const float VIEW_RIGHT_BOUND = VIEW_SIZE_WIDTH*0.5f;

static std::string fontList[] = {"SeoulNamsan CB", "Marker Felt", "arial"};

#endif /* defined(__TinyRPG__TinyRPGProperties__) */
