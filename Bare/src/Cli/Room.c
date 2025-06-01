#include <Room.imp.h>
#include <Dbg.h>

#define dbg_prefix "[ReqRoomLobby] "

ae2f_SHAREDEXPORT 
void ReqRoomLobby(
    sock_t svrsock, const sockaddr_t* svraddr
    , room_t room, room_t* retroom, const char* name
    , const char* pw, const char* clientname
) {
    dbg_puts("Starting.");
    assertmsg((svrsock == -1) == SERVER);
    assertmsg(!svraddr == SERVER);
    __ReqRoomLobby(svrsock, svraddr, room, retroom, name, pw, clientname);
    dbg_puts("done gracully.");
}

ae2f_SHAREDEXPORT
void ReqRoomShow(
    sock_t svrsock, const sockaddr_t* svraddr
    , room_t roompad, room_t roomcount, Room* retroom, room_t* retcount
) {
   if(!((svraddr) && (retroom) && (retcount)));
   else if(roompad + roomcount > MAX_ROOM_COUNT) {
    *(retcount) = 0;
   }
   {
    union { sockaddr_internal_t _in[1]; sockaddr_t addr[1]; } v_svraddr;
    __ReqRoomShowBuf v_showbuf;

    v_showbuf.m_req = REQ_ROOMSHOW;
    v_showbuf.count = roomcount;
    v_showbuf.pad = roompad;

    if (sendto(
        svrsock, (void*)&v_showbuf
        , sizeof(v_showbuf), 0
        , svraddr, sizeof(*svraddr)
    ) != sizeof(__ReqRoomShowBuf)) {
        *(retcount) = 0;
    } else {

        *(retcount) = (sizeof(Room) * roomcount) != recvfrom(
                    svrsock, (void*)retroom
                    , sizeof(Room) * roomcount
                    , 0, v_svraddr.addr, 0
                );
        
        if(!sockaddr_internal_check((const sockaddr_internal_t*)svraddr, v_svraddr._in)) {
            *(retcount) = 0;
        }
    }
   }
}

#define dbg_prefix