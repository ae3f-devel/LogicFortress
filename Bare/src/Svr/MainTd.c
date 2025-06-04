#define SERVER 1
#include "./SvrMain.h"
#include <Dbg.h>
#include <Room.h>
#include <Req.h>

#if _WIN32

#define nonblock(sock, res)  \
{ \
    u_long mode = 1; \
    if (ioctlsocket(sock, FIONBIO, &mode) != 0) { \
        dbg_printf("ioctlsocket failed with error: %d\n", WSAGetLastError()); \
        *(res) = -1; \
    } \
    *(res) = 0; \
}

#define errno WSAGetLastError()
#define EWOULDBLOCK   WSAEWOULDBLOCK
#define EAGAIN        WSAEWOULDBLOCK

#else
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define nonblock(fd, res)                                                      \
  if (res) {                                                                   \
    int v_flags;                                                               \
    v_flags = fcntl(fd, F_GETFL, 0);                                           \
                                                                               \
    if (v_flags == -1) {                                                       \
      dbg_puts("fcntl F_GETFL");                                               \
      *(res) = -1;                                                             \
    } else {                                                                   \
                                                                               \
      /* Add non-blocking flag */                                              \
      v_flags |= O_NONBLOCK;                                                   \
      if (fcntl(fd, F_SETFL, v_flags) == -1) {                                 \
        perror("fcntl F_SETFL");                                               \
        *(res) = -1;                                                            \
      } else                                                                   \
        *(res) = 0;                                                            \
    }                                                                          \
  }

#endif



#undef dbg_prefix
#define dbg_prefix "[SvrUnit] "

ae2f_extern ae2f_SHAREDEXPORT void SvrUnit(union _SvrUnit *a) {
  if (!a)
    return;

  if (a->ID.fd == INVALID_SOCKET)
    return;

  dbg_printf("thread %p has started\n", a - SvrUnits);
  Rooms[a->Game.room].m_started = 0;
  RoomFlags[a->Game.room] = 0;

  while (a->ID.fd != INVALID_SOCKET) {
    dbg_puts("Waiting...");
    __ae2f_Wait(RoomFlags + a->Game.room, 0);
    dbg_puts("Waiting is over");
  }

  __QUIT:
  dbg_printf("thread %p is over\n", a - SvrUnits);
}

#undef dbg_prefix
#define dbg_prefix "[SvrRes] "

ae2f_extern ae2f_SHAREDEXPORT 
void SvrRes(union _SvrUnit *a) {
  if (!a)
    return;

  dbg_printf("thread %p has started\n", a - SvrUnits);

  {
    int res;
    nonblock(a->ID.fd, &res);
  }

  _Svr Svr = {0, };
  Svr.m_sock = a->ID.fd;

  while (a->ID.fd != INVALID_SOCKET) {
    if(!RoomFlags[MAX_ROOM_COUNT]) {
      RoomFlags[MAX_ROOM_COUNT] = 1;
      __ae2f_WakeSingle(&RoomFlags[MAX_ROOM_COUNT]);
    }

    Svr.m_addrlen = sizeof(Svr.m_addr.m_in);

    Svr.m_succeed =
        recvfrom(Svr.m_sock, (void *)&Svr.m_reqbuff, sizeof(Svr.m_reqbuff), 0,
                 Svr.m_addr.m_addr, &Svr.m_addrlen);

    if (Svr.m_succeed < sizeof(req_t) || Svr.m_succeed > sizeof(Svr.m_reqbuff)) {
      if(errno == EWOULDBLOCK || errno == EAGAIN) {
        continue;
      } else if(a->ID.fd == INVALID_SOCKET) {
        break;
      }

      continue;
    }

    if(Svr.m_succeed >= sizeof(req_t)) {
      dbg_printf("Connect from somewhere. Req: %d\n", Svr.m_reqbuff.m_req);
    }
    switch (Svr.m_reqbuff.m_req) {
    case REQ_ROOMLOBBY:
      if(Svr.m_succeed != sizeof(Svr.m_reqbuff.m_ReqRoomLobby)) continue;;
      ResRoomLobby(Svr.m_sock, Svr.m_addr.m_addr,
                   &Svr.m_reqbuff.m_ReqRoomLobby);
      break;
    case REQ_ROOMSHOW:
      if(Svr.m_succeed != sizeof(Svr.m_reqbuff.m_ReqRoomShow)) continue;;
      ResRoomShow(Svr.m_sock, Svr.m_addr.m_addr, &Svr.m_reqbuff.m_ReqRoomShow);
      break;
    }
  }

  dbg_printf("thread %p is over\n", a - SvrUnits);
}
