#ifndef SvrMain_h
#define SvrMain_h

#include <Max.auto.h>
#include <Room.h>
#include <ae2f/Atom.h>
#include <ae2f/Call.h>
#include <ae2f/Cast.h>

ae2f_extern ae2f_SHAREDCALL union _SvrUnit {
  struct _SvrUnitID {
    ae2f_Atom(sock_t) fd;
#ifdef __cplusplus
    constexpr _SvrUnitID() : fd(INVALID_SOCKET) {}
    inline ~_SvrUnitID() {}
#endif
  } ID;

  struct _SvrUnitGame {
    struct _SvrUnitID _;
    room_t room;
  } Game;
#ifdef __cplusplus
  constexpr _SvrUnit() : ID() {}
  inline ~_SvrUnit() {}
#endif
} SvrUnits[MAX_ROOM_COUNT + 1];

#ifdef __cplusplus
#include <thread>
ae2f_extern ae2f_SHAREDCALL union _SvrUnitIDHandle {
  std::thread td;
  char a;
  inline ~_SvrUnitIDHandle() {}
  constexpr _SvrUnitIDHandle() : a(0) {}
} SvrTds[MAX_ROOM_COUNT + 1];
#endif

#include "./ReqBuff.h"

typedef struct _Svr {
  ae2f_InetMkData m_mkdata;
  sock_t m_sock;
  ReqBuff m_reqbuff;
  uSockAddr m_addr[1];
  socklen_t m_addrlen;
  ssize_t m_succeed;
} _Svr;

#include "./RoomFlags.h"

ae2f_extern ae2f_SHAREDCALL _Svr Svr;

#endif
