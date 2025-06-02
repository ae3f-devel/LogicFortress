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
                                    __ReqRoomLobbyBuf *req) {
    if (req && req->m_req == REQ_ROOMLOBBY && addr &&
        sock != INVALID_SOCKET) {
      room_t v_retroom = -1;
      __RoomLobby(req->m_room, &v_retroom, req->m_rname, req->m_rpwd, sock,
                  addr, req->m_plname);
      if (sizeof(room_t) == sendto(sock, (const void*)&v_retroom, sizeof(v_retroom), 0, addr,
                                   sizeof(sockaddr_internal_t))) {
      }
    }  
}

#define dbg_prefix "[ResRoomShow] "

ae2f_SHAREDCALL
void ResRoomShow(sock_t clisock, const sockaddr_t* cliaddr, __ReqRoomShowBuf* req) {
  if((req) && (cliaddr) && clisock != INVALID_SOCKET) {
    dbg_printf("pad %d + count %d = %d\n", req->pad, req->count, req->count + req->pad);
    if(req->pad + req->count <= MAX_ROOM_COUNT) {
      dbg_puts("Got. sending room informations.");
      ssize_t a = sendto(clisock, ae2f_reinterpret_cast(const void*, Rooms + req->pad), sizeof(Room) * req->count, 0, cliaddr, sizeof(sockaddr_internal_t));
      dbg_printf("sendto: %d\n", a);
    }
  }
}
