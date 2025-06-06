#ifndef Player_h
#define Player_h

#include <ae2f/Cast.h>
#include <ae2f/Call.h>

#include "./Max.auto.h"
#include "./Sock.h"

#include <ae2f/Pack/Beg.h>
#include "./Util.h"
#include "./Player.auto.h"

typedef struct Player {
    char        m_Name[MAX_PLAYER_NAME_COUNT];
} Player;

#include <ae2f/Pack/End.h>



#if SERVER
ae2f_extern ae2f_SHAREDCALL Player    Players[MAX_GLOBAL_PLAYER_COUNT];
#endif

#endif