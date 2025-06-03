#ifndef Room_h
#define Room_h

#include <ae2f/Call.h>
#include <ae2f/Cast.h>

#include "./Max.auto.h"
#include "./Sock.h"

#include <ae2f/Pack/Beg.h>
#include <time.h>
#include "./Room.auto.h"

#include "./WaitWake.h"

#pragma pack(push, 1)

/**
 * @brief
 * Global settings or something.
 */
typedef struct Room {
  char m_Name[MAX_ROOM_NAME_COUNT];
  int m_started;
  size_t m_member;

#ifdef __cplusplus
  constexpr Room() : m_Name{0, }, m_started(0), m_member{0} {}
#endif
} Room;

#pragma pack(pop)

#include "./Req.h"

#include <ae2f/Pack/End.h>

typedef struct __ReqRoomLobbyBuf __ReqRoomLobbyBuf; 
typedef struct __ReqRoomShowBuf __ReqRoomShowBuf;

#if SERVER

typedef struct RoomPrivate {
  char m_Pw[MAX_ROOM_PW];
} RoomPrivate;

ae2f_extern ae2f_SHAREDCALL Room Rooms[MAX_ROOM_COUNT];
ae2f_extern ae2f_SHAREDCALL RoomPrivate RoomPrivates[MAX_ROOM_COUNT];
ae2f_extern ae2f_SHAREDCALL void RoomLobby(room_t room, room_t *retroom,
                                           const char *roomname, const char *pw,
                                           sock_t clientsocket,
                                           const sockaddr_t *clientaddr,
                                           const char *clientname);


ae2f_extern ae2f_SHAREDCALL void ResRoomLobby(sock_t clientsocket,
                                           const sockaddr_t *clientaddr, __ReqRoomLobbyBuf* req);

ae2f_extern ae2f_SHAREDCALL void ResRoomShow(sock_t clisock, const sockaddr_t* cliaddr, __ReqRoomShowBuf* req);
#else
#endif

ae2f_extern ae2f_SHAREDCALL void ReqRoomLobby(sock_t svrsock,
                                              const sockaddr_t *svraddr,
                                              room_t room, room_t *retroom,
                                              const char *roomname, const char *pw, const char* playername);

ae2f_extern ae2f_SHAREDCALL void ReqRoomShow(
    sock_t svrsock, const sockaddr_t* svraddr
    , room_t roompad, room_t roomcount, Room* retroom, room_t* retcount
);


#pragma pack(push, 1)

/** Request type utility for networking */
struct __ReqRoomLobbyBuf {
  req_t m_req; /** Request type for server */
  room_t m_room; /** Room ID  */
  char m_plname[MAX_PLAYER_NAME_COUNT]; /** Player name */
  char m_rname[MAX_ROOM_NAME_COUNT];    /** Room Name (when you are making new) */
  char m_rpwd[MAX_ROOM_PW];             /** Password */
};

struct __ReqRoomShowBuf {
  req_t m_req;
  room_t pad;
  room_t count;
};

#pragma pack(pop)

#if 0

ae2f_extern ae2f_SHAREDCALL
globplayer_t GetPlayerIdx(room_t, player_t);

ae2f_extern ae2f_SHAREDCALL
room_t       GetRoomIdx(globplayer_t);

#endif

#endif
