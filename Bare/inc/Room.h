#ifndef Room_h
#define Room_h

#include <ae2f/Cast.h>
#include <ae2f/Call.h>

#include "./Sock.h"
#include "./Max.auto.h"

#include <ae2f/Pack/Beg.h>
#include <time.h>

/** 
 * @brief
 * Global settings or something.
 */
typedef struct Room {
    char m_Name[MAX_ROOM_NAME_COUNT];
    char m_Pw[MAX_ROOM_PW];
    bool m_started;

#ifdef __cplusplus
    constexpr Room() : m_Name{0, }, m_Pw{0, }, m_started(0) {}
#endif
} Room;

#include <ae2f/Pack/End.h>

typedef unsigned room_t;

#if SERVER
ae2f_extern ae2f_SHAREDCALL Room    Rooms[MAX_ROOM_COUNT];
ae2f_extern ae2f_SHAREDCALL void RoomLobby(room_t room, room_t* retroom, const char* name, const char* pw);

#else
#define __RoomLobby(...)

#endif

ae2f_extern ae2f_SHAREDCALL
void ReqRoomLobby(sock_t svrsock, const sockaddr_t* svraddr, room_t room, room_t* retroom, const char* name, const char* pw);


#if 0

ae2f_extern ae2f_SHAREDCALL
globplayer_t GetPlayerIdx(room_t, player_t);

ae2f_extern ae2f_SHAREDCALL
room_t       GetRoomIdx(globplayer_t);

#endif


#endif