#include <Dbg.h>
#include <Room.imp.h>

#define dbg_prefix "[RoomLobby] "


ae2f_SHAREDEXPORT void RoomLobby(room_t room, room_t *retroom,
                                 const char *name_room, const char *pw,
                                 sock_t sock, const sockaddr_t *addr,
                                 const char *name_member) {
  __RoomLobby(room, retroom, name_room, pw, sock, addr, name_member);
}

ae2f_SHAREDEXPORT void ResRoomLobby(sock_t sock, const sockaddr_t *addr,
                                    __ReqRoomLobbyBuf *req,
                                    uint8_t *flag_keep) {
  if (flag_keep) {
    if (*(flag_keep) && req && req->m_req == REQ_ROOMLOBBY && addr &&
        sock != INVALID_SOCKET) {
      room_t v_retroom = -1;
      __RoomLobby(req->m_room, &v_retroom, req->m_rname, req->m_rpwd, sock,
                  addr, req->m_plname);
      if (sizeof(room_t) == sendto(sock, &v_retroom, sizeof(v_retroom), 0, addr,
                                   sizeof(sockaddr_internal_t))) {
        *(flag_keep) = 0; /*succeed*/
      }
    }
  }
}
