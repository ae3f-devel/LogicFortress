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

#if SERVER
    sock_t      m_sock;
    sockaddr_t  m_addr;
#endif

#ifdef __cplusplus
    constexpr Player() : m_Name{0, } when_SERVER(, m_sock(INVALID_SOCKET), m_addr{0, }) {}
#endif
} Player;

#include <ae2f/Pack/End.h>



#if SERVER
ae2f_extern ae2f_SHAREDCALL Player    Players[(MAX_ROOM_PLAYER_COUNT + MAX_ROOM_SPECTATOR_COUNT) * MAX_ROOM_COUNT];
#endif

#endif