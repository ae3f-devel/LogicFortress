#include <Max.auto.h>

#include <Player.h>
#include <Room.h>

ae2f_extern ae2f_SHAREDEXPORT Player  Players   [(MAX_ROOM_PLAYER_COUNT + MAX_ROOM_SPECTATOR_COUNT) * MAX_ROOM_COUNT];
ae2f_extern ae2f_SHAREDEXPORT Room    Rooms     [MAX_ROOM_COUNT];

