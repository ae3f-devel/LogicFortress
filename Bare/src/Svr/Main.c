#include <Sock.imp.h>

ae2f_SHAREDEXPORT
struct Svr {
    ae2f_InetMkData mkdata;
    sock_t sock;
} Svr;

#include <threads.h>
#include <Room.auto.h>
#include <Max.auto.h>

ae2f_SHAREDEXPORT
union _SvrUnit {
    struct _SvrUnitID {
        thrd_t id;
        int res;
    } ID;

    struct _SvrUnitGame {
        struct _SvrUnitID _;
        room_t room;
    } Game;
} Units[MAX_ROOM_COUNT + 1];


ae2f_SHAREDCALL int SvrUnit(void*);
ae2f_SHAREDCALL int SvrRes(void*);

/**
 * @brief 
 * @param port 
 * @returns 0 when succeed.
 */
ae2f_SHAREDEXPORT
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

    thrd_create(&Units->ID.id, SvrRes, Units);

    for(room_t i = 0; i < MAX_ROOM_COUNT; i++) {
        Units[i + 1].Game.room = i;
        thrd_create(&Units[i + 1].ID.id, SvrUnit, Units + i + 1);
    }

    return 0;
}

ae2f_SHAREDEXPORT
void SvrExit() {
    for(size_t i = sizeof(Units) / sizeof(Units[0]) - 1; i != -1; i--) {
        thrd_join(Units[i].ID.id, &Units[i].ID.res);
    }

    close(Svr.sock);
    ae2f_InetDel();
}