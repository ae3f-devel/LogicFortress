#include <Room.imp.h>
#include <Dbg.h>

#define dbg_prefix "[RoomLobby] "

ae2f_SHAREDEXPORT 
void RoomLobby(room_t room, room_t* retroom, const char* name, const char* pw) {
    assertmsg(retroom);

    dbg_puts("Starting.");

    if(!(retroom));
    else if(room != -1) {
        unsigned v_occupied;
        __IsRoomNOccupied(Rooms + (room), &v_occupied);

        if(v_occupied) {
            dbg_printf("This room[%d] is not configured. Are you making one?\n", (room));
        } else {
            dbg_printf("The room %d is occupied by someone.\n", (room));
            __IsRoomNFull(Rooms + (room), &v_occupied);
            if(v_occupied) {
                dbg_printf("The room %d is valid.\n", (room));
                if((pw) && !strncmp(Rooms[(room)].m_Pw, (pw), MAX_ROOM_PW)) {
                    dbg_puts("Password matches. You may come in.");
                    Rooms[(room)];
                } else {
                    dbg_puts("Password does not matches.");
                    *(retroom) = -1;
                }
            } else {
                dbg_printf("The room %d is full. \n", (room));
            }
        }
    }

    dbg_puts("Done gracully.");
}