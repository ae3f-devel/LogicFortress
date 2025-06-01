#define SERVER 1
#include "./SvrMain.h"
#include <Room.h>

ae2f_SHAREDEXPORT void SvrUnit(union _SvrUnit* a) {
    while(1) {
        if(!Rooms[a->Game.room].m_started);
    }
}

ae2f_SHAREDEXPORT void SvrRes(union _SvrUnit* a) {
    if(!a) return;

    _Svr Svr;
    Svr.m_sock = a->ID.fd;
    
    while(a->ID.fd != INVALID_SOCKET) {
        Svr.m_succeed = recvfrom(
            Svr.m_sock,
            (void*)&Svr.m_reqbuff,
            sizeof(Svr.m_reqbuff), 
            0, 
            Svr.m_addr.m_addr, 
            &Svr.m_addrlen
        );

        if(Svr.m_succeed < sizeof(req_t)) continue;

        switch(Svr.m_reqbuff.m_req) {
            case REQ_ROOMLOBBY:
                ResRoomLobby(
                    Svr.m_sock
                    , Svr.m_addr.m_addr
                    , &Svr.m_reqbuff.m_ReqRoomLobby
                );
            break;
            case REQ_ROOMSHOW:
                ResRoomShow(
                    Svr.m_sock
                    , Svr.m_addr.m_addr
                    , &Svr.m_reqbuff.m_ReqRoomShow
                );
            break;
        }
    }
}