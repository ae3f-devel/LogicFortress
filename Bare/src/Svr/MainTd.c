#define SERVER 1
#include "./SvrMain.h"
#include <Dbg.h>
#include <Room.h>

#undef dbg_prefix
#define dbg_prefix "[SvrUnit]"

#if _WIN32
#else
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#endif

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
        *(res) - 1;                                                            \
      } else                                                                   \
        *(res) = 0;                                                            \
    }                                                                          \
  }

ae2f_extern ae2f_SHAREDEXPORT void SvrUnit(union _SvrUnit *a) {
  if (!a)
    return;

  if (a->ID.fd == INVALID_SOCKET)
    return;

  dbg_printf("thread %p has started\n", a - SvrUnits);

  while (a->ID.fd != INVALID_SOCKET) {
    if (!Rooms[a->Game.room].m_started)
      ;
  }

  dbg_printf("thread %p is over\n", a - SvrUnits);
}

#undef dbg_prefix
#define dbg_prefix "[SvrRes]"

ae2f_extern ae2f_SHAREDEXPORT 
void SvrRes(union _SvrUnit *a) {
  if (!a)
    return;

  dbg_printf("thread %p has started\n", a - SvrUnits);

  {
    int res;
    nonblock(a->ID.fd, &res);
  }

  _Svr Svr;
  Svr.m_sock = a->ID.fd;

  while (a->ID.fd != INVALID_SOCKET) {
    Svr.m_succeed =
        recvfrom(Svr.m_sock, (void *)&Svr.m_reqbuff, sizeof(Svr.m_reqbuff), 0,
                 Svr.m_addr.m_addr, &Svr.m_addrlen);

    if (Svr.m_succeed < sizeof(req_t)) {
      if(errno == EWOULDBLOCK || errno == EAGAIN) {
        continue;
      } else if(a->ID.fd == INVALID_SOCKET) {
        break;
      }

      continue;
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
