#include "./PlConn.h"
#include "./Room.imp.h"
#include "./Sock.imp.h"
#include <Dbg.h>
#include_next <Player.imp.h>
#include <ae2f/Cast.h>
#include <string.h>

#define __IsPlayerNull(p) (!(p)->m_connected)

#undef uSockAddrInCheck
#define uSockAddrInCheck(a, b)                                                 \
  (/* (a)->m_in.sin_family == (b)->m_in.sin_family && */                       \
   (a)->m_in.sin_addr.s_addr ==                                                \
   (b)->m_in.sin_addr.s_addr /* (a)->m_in.sin_port == (b)->m_in.sin_port */)

#define __SetPlayerOffline(addr, retidx)                                       \
  for (*(retidx) = 0; *(retidx) < MAX_GLOBAL_PLAYER_COUNT; (*(retidx))++) {    \
    if (uSockAddrInCheck((addr), (&PlConns[*(retidx)].m_addr))) {              \
      memset(&PlConns[*(retidx)].m_addr, 0,                                    \
             sizeof(PlConns[*(retidx)].m_addr));                               \
      PlConns[*(retidx)].m_connected = 0;                                      \
      if (!(--Rooms[(*(retidx)) / MAX_ROOM_MEM_COUNT].m_member)) {             \
        __RoomTerminate(&Rooms[(*(retidx)) / MAX_ROOM_MEM_COUNT]);             \
      }                                                                        \
      {                                                                        \
        dbg_printf("Got someone offline: %d\n", (*retidx));                    \
        break;                                                                 \
      }                                                                        \
    }                                                                          \
  }                                                                            \
  __uSockAddrPrint(addr);                                                      \
  __uSockAddrPrint(&PlConns[0].m_addr);                                        \
  __uSockAddrPrint(&PlConns[1].m_addr);

#define __SetPlayerOnline(addr, globidx)                                       \
  dbg_puts("__SetPlayerOnline");                                               \
  if ((addr) && __IsPlayerNull((globidx) + PlConns)) {                         \
    dbg_puts("__SetPlayerOnline: ON");                                         \
    PlConns[globidx].m_addr = *(addr);                                         \
    PlConns[globidx].m_connected = 1;                                          \
    if (Rooms[(globidx) / MAX_ROOM_MEM_COUNT].m_member++) {                    \
      __RoomActivate(&Rooms[(globidx) / MAX_ROOM_MEM_COUNT]);                  \
    }                                                                          \
  }
