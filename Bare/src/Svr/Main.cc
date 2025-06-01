#include <Sock.imp.h>

ae2f_extern ae2f_SHAREDCALL
struct _Svr {
    ae2f_InetMkData mkdata;
    sock_t sock;
} Svr;

ae2f_extern ae2f_SHAREDEXPORT
_Svr Svr = {};

#include <thread>
#include <new>
#include <cstdlib>

#include <Room.auto.h>
#include <Max.auto.h>

ae2f_extern ae2f_SHAREDCALL
union _SvrUnit {
    struct _SvrUnitID {
        union _SvrUnitIDHandle {
            std::thread td; 
            char a; 
            inline ~_SvrUnitIDHandle() {} 
            constexpr _SvrUnitIDHandle() : a(0) {}
        } id;
        int res;

        constexpr _SvrUnitID() : res(0) {}
        inline ~_SvrUnitID() {}
    } ID;

    struct _SvrUnitGame {
        struct _SvrUnitID _;
        room_t room;
    } Game;

    constexpr _SvrUnit() : ID{} {}
    inline ~_SvrUnit() {}

} SvrUnits[MAX_ROOM_COUNT + 1];

ae2f_extern ae2f_SHAREDEXPORT
_SvrUnit SvrUnits[MAX_ROOM_COUNT + 1] = {};


ae2f_SHAREDCALL void SvrUnit(void*);
ae2f_SHAREDCALL void SvrRes(void*);


ae2f_SHAREDEXPORT void SvrUnit(void*) {}
ae2f_SHAREDEXPORT void SvrRes(void*) {}

/**
 * @brief 
 * @param port 
 * @returns 0 when succeed.
 */
ae2f_extern ae2f_SHAREDEXPORT
int SvrMain(unsigned short port)
{
	if (ae2f_InetMk(MAKEWORD(2, 2), &Svr.mkdata) != 0) {
        return 1;
    }

    sock_t svrfd = 0;
    union {
        sockaddr_t addr; 
        sockaddr_internal_t in[1]; 
    } svraddr;

    if((svrfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        
        close(svrfd);
        return 1;
    }

    __SockAddrMkVerbose(svraddr.in, INADDR_ANY, port);

    if(bind(svrfd, &svraddr.addr, sizeof(sockaddr_t))) {
        close(svrfd);
        return (1);
    }

    Svr.sock = svrfd;

    new (&SvrUnits->ID.id.td) std::thread(SvrRes, (void*)(SvrUnits));

    for(room_t i = 0; i < MAX_ROOM_COUNT; i++) {
        SvrUnits[i + 1].Game.room = i;
        new (&SvrUnits[i + 1].ID.id.td) std::thread(SvrUnit, (void*)(SvrUnits + i + 1));
    }

    return 0;
}

ae2f_extern ae2f_SHAREDEXPORT
void SvrExit() {
    for(size_t i = sizeof(SvrUnits) / sizeof(SvrUnits[0]) - 1; i != -1; i--) {
        SvrUnits[i].ID.id.td.join();
        SvrUnits[i].ID.id.td.~thread();
    }

    close(Svr.sock);
    ae2f_InetDel();
}