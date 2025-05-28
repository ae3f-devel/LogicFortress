#include "./Room.h"

#include "./Req.h"
#include <stddef.h>
#include <string.h>

#define  __GetPlayerIndex(roomid, playerid) ((((roomid)) * MAX_ROOM_PLAYER_COUNT) + (playerid))
#define  __GetRoomIndex(globplayerid)       ((globplayerid) / MAX_ROOM_PLAYER_COUNT)

#define __ReqRoomLobby(svrsock, svraddr, room, retroom, name, pw) \
{ \
    if(!((svraddr) && (retroom))); \
    if((!(svraddr) || (svrsock) == INVALID_SOCKET))  { \
        if(SERVER) { __RoomLobby(room, retroom, pw); } \
        else { *(retroom) = -1; } \
    } \
    else { \
        uint8_t v_req[sizeof(req_t) + sizeof(room_t) + MAX_ROOM_PW]; \
        size_t v_bytes; \
\
        *ae2f_reinterpret_cast(uint8_t*, v_req) = REQ_ROOMLOBBY; \
        *ae2f_reinterpret_cast(room_t*, v_req + sizeof(req_t)) = room; \
        if(name) strncpy(v_req + sizeof(req_t) + sizeof(room_t), (name), MAX_ROOM_NAME_COUNT); \
        if(pw) strncpy(v_req + sizeof(req_t) + sizeof(room_t) + MAX_ROOM_NAME_COUNT, (pw), MAX_ROOM_PW); \
        v_bytes = sendto((svrsock), &v_req, sizeof(v_req), 0, (svraddr), sizeof(sockaddr_internal_t)); \
\
        if(v_bytes != sizeof(v_req)) { \
            (*(retroom) = -1); \
        } \
\
        else { \
            v_bytes = recvfrom((svrsock), retroom, sizeof(room_t), 0, 0, 0); \
            if(v_bytes != sizeof(v_req)) { \
                (*(retroom) = -1); \
            } \
        } \
    } \
}

#define __IsRoomCustom(r) !((r)->m_Name[0])
#define __IsRoomPrivate(r) ((r)->m_Pw[0])
#define __IsRoomOnGame(r)   ((r)->m_started)

#if SERVER
#include "./Player.imp.h"
#define __IsRoomNOccupied(r, ret)    \
    if(ret) for(size_t v_i = 0; v_i < MAX_ROOM_PLAYER_COUNT + MAX_ROOM_SPECTATOR_COUNT; v_i++) {\
        *(ret) = !__IsPlayerNull(Players + ((r) - Rooms) + v_i); \
        if(*(ret)) break; \
    }

#define __IsRoomNFull(r, ret)    \
    if(ret) for(size_t v_i = 0; v_i < MAX_ROOM_PLAYER_COUNT + MAX_ROOM_SPECTATOR_COUNT; v_i++) {\
        *(ret) = __IsPlayerNull(Players + ((r) - Rooms) + v_i); \
        if((*(ret))) break; \
    }
#endif