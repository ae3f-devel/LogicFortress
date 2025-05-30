#include <Room.imp.h>
#include <Dbg.h>

#define dbg_prefix "[ReqRoomLobby] "

ae2f_SHAREDEXPORT 
void ReqRoomLobby(sock_t svrsock, const sockaddr_t* svraddr, room_t room, room_t* retroom, const char* name, const char* pw, const char* clientname) {
    dbg_puts("Starting.");
    assertmsg((svrsock == -1) == SERVER);
    assertmsg(!svraddr == SERVER);
    __ReqRoomLobby(svrsock, svraddr, room, retroom, name, pw, clientname);
    dbg_puts("done gracully.");
}

#define dbg_prefix