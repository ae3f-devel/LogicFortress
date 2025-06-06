#include_next <Player.imp.h>
#include "./PlConn.h"
#include "./Sock.imp.h"
#include <string.h>
#include <Dbg.h>
#include "./Room.imp.h"

#define __IsPlayerNull(p) ((p)->m_sock == INVALID_SOCKET)

#define __SetPlayerOffline(addr, retidx)                                       \
  for (*(retidx) = 0; *(retidx) < MAX_GLOBAL_PLAYER_COUNT; (*(retidx))++) {    \
    if (addr->m_in.sin_addr.s_addr == PlConns[*(retidx)].m_addr.m_in.sin_addr.s_addr) { \
            sock_t v_sock = PlConns[*(retidx)].m_sock;  \
            memset(&PlConns[*(retidx)].m_addr, 0, sizeof(PlConns[*(retidx)].m_addr));      \
            if(!(--Rooms[(*(retidx)) / MAX_ROOM_MEM_COUNT].m_member)) { \
                __RoomTerminate(&Rooms[(*(retidx)) / MAX_ROOM_MEM_COUNT]); \
            } \
            close(v_sock);  \
            PlConns[*(retidx)].m_sock = INVALID_SOCKET; \
      { dbg_printf("Got someone offline: %d", (*retidx)); break; }                                                                   \
    } \
  } \
  __uSockAddrPrint(addr); \
  __uSockAddrPrint(&PlConns[0].m_addr);


#define __SetPlayerOnline(addr, globidx) \
  if((addr) && __IsPlayerNull((globidx) + PlConns)) { \
    sock_t v_sock = socket(AF_INET, SOCK_DGRAM, 0); \
    if((v_sock != INVALID_SOCKET)) { \
        PlConns[globidx].m_addr = *(addr); \
        Rooms[(globidx) / MAX_ROOM_MEM_COUNT].m_member++; \
        PlConns[globidx].m_sock = v_sock; \
    } \
  }
