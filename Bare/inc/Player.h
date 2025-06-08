#ifndef Player_h
#define Player_h

#include <ae2f/Call.h>
#include <ae2f/Cast.h>

#include "./Max.auto.h"
#include "./Sock.h"

#include "./Player.auto.h"
#include "./Util.h"
#include <ae2f/Pack/Beg.h>

#pragma pack(push, 1)

typedef struct Player {
  char m_Name[MAX_PLAYER_NAME_COUNT];
  char m_connected;
} Player;

#pragma pack(pop)

#include <ae2f/Pack/End.h>

#if SERVER
ae2f_extern ae2f_SHAREDCALL Player Players[MAX_GLOBAL_PLAYER_COUNT];
#endif

#endif
