#include "./Req.h"
#include "./Room.h"
#include "./Util.h"

#include <ae2f/Cast.h>

#include <stddef.h>
#include <string.h>

#define __GetPlayerIndex(roomid, playerid)                                     \
  ((((roomid)) * MAX_ROOM_PLAYER_COUNT) + (playerid))
  
#define __GetRoomIndex(globplayerid) \
  ((globplayerid) / MAX_ROOM_PLAYER_COUNT)

/**
 * @details
 * v_req:
 *  global:
 *    [req_t]                      : as request  \n
 *    [room_t]                     : room number \n
 *    [char[MAX_PLAYER_NAME_COUNT]]: player name \n
 *  additional when making new one [room number is -1]: \n
 *    [char[MAX_ROOM_NAME_COUNT]]  : room name   \n
 *    [char[MAX_ROOM_PW]]          : room passwd \n
 *
 * v_res:
 *  [room_t]
 */
#define __ReqRoomLobby(svrsock, svraddr, room, retgplidx, name /*opt*/,          \
                       pw /*opt*/, clientname /*opt*/)                         \
  {                                                                            \
    if (!((svraddr) && (retgplidx)))                                             \
      ;                                                                        \
    if ((!(svraddr) || (svrsock) == INVALID_SOCKET)) {                         \
      when_SERVER(                                                             \
          RoomLobby(room, retgplidx, name, pw, svrsock, svraddr, clientname));   \
      when_CLIENT(*(retgplidx) = -1);                                            \
    } else {                                                                   \
      __ReqRoomLobbyBuf v_req = {                                              \
          0,                                                                   \
      };                                                                       \
      size_t v_bytes;                                                          \
                                                                               \
      v_req.m_req = REQ_ROOMLOBBY;                                             \
      v_req.m_room = room;                                                     \
      if (clientname)                                                          \
        strncpy(v_req.m_plname, clientname, MAX_PLAYER_NAME_COUNT);            \
      if ((room) == -1) {                                                      \
        if (name)                                                              \
          strncpy(v_req.m_rname, (name), MAX_ROOM_NAME_COUNT);                 \
        if (pw)                                                                \
          strncpy(v_req.m_rpwd, (pw), MAX_ROOM_PW);                            \
      }                                                                        \
      v_bytes = sendto((svrsock), (const void*)&v_req, sizeof(v_req), 0, (svraddr),         \
                       sizeof(sockaddr_internal_t));                           \
                                                                               \
      if (v_bytes != sizeof(v_req)) {                                          \
        (*(retgplidx) = -1);                                                     \
      }                                                                        \
                                                                               \
      else {                                                                   \
        sockaddr_internal_t v_from[1];                                         \
        socklen_t v_fromlen[1] = {sizeof(sockaddr_t)};                         \
        if (recvfrom((svrsock), (void*)(retgplidx), sizeof(room_t), 0,                  \
                     ae2f_reinterpret_cast(sockaddr_t *, v_from),              \
                     v_fromlen) != sizeof(room_t)) {                           \
          (*(retgplidx) = -1);                                                   \
        }                                                                      \
        if (!sockaddr_internal_check(                                          \
                v_from,                                                        \
                ae2f_reinterpret_cast(sockaddr_internal_t *, svraddr))) {      \
          (*(retgplidx) = -1); /* invalid, socket address does not match. */     \
        }                                                                      \
      }                                                                        \
    }                                                                          \
  }

#define __IsRoomCustom(r) !((r)->m_Name[0])
#define __IsRoomPrivate(r) ((r)->m_Pw[0])
#define __IsRoomOnGame(r) ((r)->m_started)

#if SERVER
#include "./Player.imp.h"

/** When ret_i is MAX, it is blank */
#define __IsRoomNOccupied(r, ret_i)                                            \
  if (ret_i) {                                                                  \
    for (*(ret_i) = 0; *(ret_i) < MAX_ROOM_MEM_COUNT; (*(ret_i))++) {          \
      if (!__IsPlayerNull(Players + ((r) - Rooms) + *(ret_i)))                 \
        break;  /** Not blank */                                                                \
    } /** Blank */}

#define __IsRoomNFull(r, ret_i, addr)                                          \
  if (ret_i)                                                                   \
    for (*(ret_i) = 0; *(ret_i) < MAX_ROOM_MEM_COUNT; (*(ret_i))++) {          \
      if (__IsPlayerNull(Players + (((r) - Rooms) * MAX_ROOM_MEM_COUNT) +      \
                         *(ret_i)))                                            \
        break;                                                                 \
      if (sockaddr_internal_check(                                             \
              ae2f_reinterpret_cast(const sockaddr_internal_t *, addr),        \
              ae2f_reinterpret_cast(                                           \
                  const sockaddr_internal_t *,                                 \
                  &(Players + (((r) - Rooms) * MAX_ROOM_MEM_COUNT) + *(ret_i)) \
                       ->m_addr)))                                             \
        break;                                                                 \
    }

#define __FindRoomNOccupied(reti)                                              \
  if (reti) {                                                                  \
    for (*(reti) = 0; *(reti) < MAX_ROOM_COUNT; (*(reti))++) {                 \
      player_t v_i;                                                              \
      v_i = 0;                                                                 \
      __IsRoomNOccupied(Rooms + *(reti), &v_i);                                \
      /* world is blank. this is what we wanted. */                            \
      if (v_i == MAX_ROOM_MEM_COUNT)                                           \
        break;                                                                 \
    }                                                                          \
  }

#define __FindRoomMatchAvailable(reti, pl) \
  for(*(reti) = 0; *(reti) < MAX_ROOM_COUNT; (*(reti))++) { \
    for(*(pl) = 0; *(pl) < MAX_ROOM_PLAYER_COUNT; (*(pl))++) { \
      if(__IsPlayerNull(&Players[*(reti) * MAX_ROOM_MEM_COUNT + *(pl)])) break; \
    } \
    if(*(pl) != MAX_ROOM_PLAYER_COUNT) break; \
  }

#define __RoomLobby(room, retgplidx, name_room, pw, sock, addr, name_member)     \
  {                                                                            \
    assertmsg(retgplidx);                                                        \
    dbg_puts("Starting.");                                                     \
                                                                               \
    if (!(retgplidx))                                                            \
      ;                                                                        \
    else { \
        globplayer_t v_globplayer_i = 0;                                             \
        __SetPlayerOffline(addr, &v_globplayer_i);                               \
        if(v_globplayer_i != MAX_GLOBAL_PLAYER_COUNT) { \
          dbg_puts("you are online.");                           \
          dbg_printf("You are online here -> %d\n", v_globplayer_i);             \
          dbg_puts("Now you are being disconnected.");                           \
          *(retgplidx) = -1;                                                       \
        } \
        if ((room) == -1 && v_globplayer_i != MAX_GLOBAL_PLAYER_COUNT); \
        else if((room) == -1) {                                                                 \
          /** Making new room... */                                              \
          room_t reti; globplayer_t pl = 0;                                                           \
          if((name_room) && *(name_room)) { __FindRoomNOccupied((&reti)); }          \
          else { __FindRoomMatchAvailable(&reti, &pl); } \
          \
          if (reti == MAX_ROOM_COUNT) {                                          \
            dbg_puts("No room is available.");                                   \
            *(retgplidx) = -1;                                                     \
          } else {                                                               \
            dbg_printf("Room %d will be allocated.\n");                          \
            *(retgplidx) = (reti) * MAX_ROOM_MEM_COUNT + pl;                                                   \
            if (name_room)                                                       \
              strncpy(Rooms[reti].m_Name, name_room, MAX_ROOM_NAME_COUNT);       \
            else                                                                 \
              Rooms[reti].m_Name[0] = 0;                                         \
                                                                                \
            if (pw)                                                              \
              strncpy(RoomPrivates[reti].m_Pw, pw, MAX_ROOM_PW);                        \
            else                                                                 \
              RoomPrivates[reti].m_Pw[0] = 0;                                           \
                                                                                \
            Players[reti * MAX_ROOM_MEM_COUNT + (pl)].m_sock = sock;                    \
            if (addr)                                                            \
              Players[reti * MAX_ROOM_MEM_COUNT + (pl)].m_addr = *(addr);               \
                                                                                \
            if (name_member)                                                     \
              strncpy(Players[reti * MAX_ROOM_MEM_COUNT + (pl)].m_Name, name_member,    \
                      MAX_PLAYER_NAME_COUNT);                                    \
            else                                                                 \
              Players[reti * MAX_ROOM_MEM_COUNT + pl].m_Name[0] = 0;                  \
          }                                                                      \
        } else {                                                                       \
          /** Connected to existing... */  \
          if (Rooms[room].m_started) {                                        \
            dbg_printf("This room[%d], is already started.\n", room);                \
            *(retgplidx) = -1;                                                         \
          } else {                                                                   \
            size_t reti;                                                             \
            __IsRoomNOccupied(Rooms + (room), &reti);                                \
                                                                               \
            if (reti == MAX_ROOM_MEM_COUNT) {                                        \
              dbg_printf("Unexpected room number %d\n", (room));                     \
              *(retgplidx) = -1;                                                       \
            } else {                                                                 \
              dbg_printf("The room %d is occupied by someone.\n", (room));           \
              __IsRoomNFull(Rooms + (room), &reti, addr);                            \
              if (reti != MAX_ROOM_MEM_COUNT) {                                      \
                dbg_printf("The room %d is valid.\n", (room));                       \
                  if (((pw) && !strncmp(RoomPrivates[(room)].m_Pw, (pw),                      \
                                MAX_ROOM_PW)) /* pw matches. */                \
                  || !RoomPrivates[(room)].m_Pw[0] /*Pwd of room is null.*/) {            \
                    dbg_puts("Password matches. You may come in.");                    \
                    *(retgplidx) = (room) * MAX_ROOM_MEM_COUNT + (reti);                                               \
                    if (addr)                                                          \
                      Players[reti + (room) * MAX_ROOM_MEM_COUNT].m_addr = *(addr);    \
                    Players[reti + (room) * MAX_ROOM_MEM_COUNT].m_sock = (sock);       \
                    if (name_member)                                                   \
                      strncpy(Players[reti + (room) * MAX_ROOM_MEM_COUNT].m_Name,      \
                      (name_member), MAX_PLAYER_NAME_COUNT);                   \
                    else                                                               \
                      Players[reti + (room) * MAX_ROOM_MEM_COUNT].m_Name[0] = 0;       \
                  } else {                                                             \
                    dbg_puts("Password does not matches.");                            \
                    *(retgplidx) = -1;                                                   \
                  }                                                                    \
                } else {                                                               \
                  dbg_printf("The room %d is full. \n", (room));                       \
                  *(retgplidx) = -1;                                                     \
                }                                                                      \
              }                                                                        \
            }                                                                          \
        } \
      } \
    dbg_puts("Done gracully.");                                                \
  }

#endif
