#include <Dbg.h>
#include <Room.imp.h>

#define dbg_prefix "[ReqRoomLobby] "

ae2f_SHAREDEXPORT void ReqRoomLobby(sock_t svrsock, const sockaddr_t *svraddr,
                                    room_t room, room_t *retroom,
                                    const char *name, const char *pw,
                                    const char *clientname) {
  dbg_puts("Starting.");
  assertmsg((svrsock == -1) == SERVER);
  assertmsg(!svraddr == SERVER); /*?*/
  __ReqRoomLobby(svrsock, svraddr, room, retroom, name, pw, clientname);
  dbg_puts("done gracully.");
}

#define dbg_prefix "[ReqRoomShow] "

ae2f_SHAREDEXPORT void ReqRoomShow(sock_t svrsock, const sockaddr_t *svraddr,
                                   room_t roompad, room_t roomcount,
                                   Room *retroom, room_t *retcount) {
  if (!((svraddr) && (retroom) && (retcount)))
    ;
  else if (roompad + roomcount > MAX_ROOM_COUNT) {
    dbg_puts("Too many: it exceeed the max");
    *(retcount) = 0;
  } else {
    union {
      sockaddr_internal_t _in[1];
      sockaddr_t addr[1];
    } v_svraddr;
    __ReqRoomShowBuf v_showbuf;

    v_showbuf.m_req = REQ_ROOMSHOW;
    v_showbuf.count = roomcount;
    v_showbuf.pad = roompad;

    if (sendto(svrsock, (void *)&v_showbuf, sizeof(v_showbuf), 0, svraddr,
               sizeof(*svraddr)) != sizeof(__ReqRoomShowBuf)) {
      dbg_puts("Sendto has failed.");
      *(retcount) = 0;
    } else {
      socklen_t v_addrlen = sizeof(sockaddr_t);
      *(retcount) = recvfrom(svrsock, (void *)retroom, sizeof(Room) * roomcount,
                             0, v_svraddr.addr, &v_addrlen);

      if ((*(retcount)) != roomcount * sizeof(Room)) {
        dbg_puts("recvfrom has failed.");
      }

#if 1
      if (!sockaddr_internal_check((const sockaddr_internal_t *)svraddr,
                                   v_svraddr._in)) {
        dbg_puts("Host is another person.");
        *(retcount) = 0;
      } else if (*(retcount) > 0) {
        *(retcount) /= sizeof(Room);
      }
#endif
    }
  }
}

#define dbg_prefix
