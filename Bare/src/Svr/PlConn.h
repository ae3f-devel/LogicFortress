#ifndef PlConn_h
#define PlConn_h

#include <Player.imp.h>
#include <ae2f/Atom.h>

typedef struct PlConn {
  uSockAddr m_addr;
  bool m_connected;
} PlConn;

ae2f_extern ae2f_SHAREDCALL PlConn PlConns[MAX_GLOBAL_PLAYER_COUNT];
#endif
