#ifndef PlConn_h
#define PlConn_h

#include <Player.imp.h>
#include <ae2f/Atom.h>

typedef struct PlConn {
    ae2f_Atom(sock_t)    m_sock;
    uSockAddr m_addr;
} PlConn;

ae2f_extern ae2f_SHAREDCALL PlConn PlConns[MAX_GLOBAL_PLAYER_COUNT];

#endif