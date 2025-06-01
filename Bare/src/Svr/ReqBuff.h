#ifndef ReqBuff_h
#define ReqBuff_h

#include <Req.h>
#include <Room.h>

typedef union ReqBuff {
    req_t m_req;
    __ReqRoomLobbyBuf m_ReqRoomLobby;
    __ReqRoomShowBuf m_ReqRoomShow;
} ReqBuff;

#endif