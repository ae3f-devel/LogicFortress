# Room
> Following is the goal of this branch.  
> We are using `ngo` library to do this things.

- Multi

# Goal
- Create Room
- Join Room
- Lobby
- Game Start

## Player
- `player_t` would play as an index. Which means it should be unsigned integer.
- Each Player must have PlayerID for powered.
- Allocating/Deallocating PlayerID is required.
- -1 will be treated as null.
```c
struct Player {
    sock_t socket; /** socket of client. available when server. */
    /* Additional Parameters */
};
```


## Room
- `room_t` would play as an index. Which means it should be unsigned integer.
- Each room must have RoomID for powered.
- Method for Allocating/Freeing RoomID is required.
- If Player has RoomID as -1, 'T will be considered as offline.
- -1 will be treated as null.
- Structure of Room would be similar to this.

```c
#define TEAM_MEMCOUNT   /** Count for one team members. */

struct Room {
    /* Additional Parameters. Usually for global settings. */
};
```

- Server would have something like this, playing a role of master list.
```c
#define ROOM_MAXCOUNT           /** Max count for room */
Room rooms[ROOM_MAXCOUNT];      /** This should be pre-allocated */
Player players[TEAM_MEMCOUNT * ROOM_MAXCOUNT];  /** This should be pre-allocated to 0. */
```

## Room
- Request RoomID from server.
- Here, you could pass `room` as wanted RoomID to be online.

- This is how it would understand your intention when you are offline.
    - Pass -1 to `room` for server to request an allocation of new room.
    - Pass 0 to `room` for play locally.

- This is how it should understand your intention when you are online.
    - Pass 0 to `room` to disconnect.

- at `retroom`, you will receive actual RoomID that you're actually online.
    - -1 means you are failed to receive a room. (connect to somewhere), or you just disconnected.
    - 0 means you are at local, maybe hosting a game.

```c
void Client.ReqRoom(sock_t svrsock, room_t room, room_t* retroom);
void Server.Room(sock_t clientsock, room_t room);
```

- It could also be used as verification after the first connect of room.

## In Room
- Get some data from server.
- This is the core of the game, which could be some data.

```c
void Client.ReqRoomGetData(sock_t svrsock, room_t room, Room* retroomdata);
void Client.RoomGetData(sock_t clientsock, room_t room);
```

## Game Start
- Must on another scene

# Util
- unspecified
