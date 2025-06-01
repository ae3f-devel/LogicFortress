#include <Sock.imp.h>
#include "./SvrMain.h"

#include <new>
#include <cstdlib>



ae2f_extern ae2f_SHAREDEXPORT
_SvrUnit SvrUnits[MAX_ROOM_COUNT + 1] = {};

ae2f_extern ae2f_SHAREDEXPORT
_SvrUnitIDHandle SvrTds[MAX_ROOM_COUNT + 1] = {};


ae2f_SHAREDCALL void SvrUnit(void*);
ae2f_SHAREDCALL void SvrRes(void*);

static unsigned SvrStarted = 0;

ae2f_extern ae2f_SHAREDCALL void SvrExit();

/**
 * @brief 
 * @param port 
 * @returns 0 when succeed.
 */
ae2f_extern ae2f_SHAREDEXPORT
int SvrMain(unsigned short port)
{
    if(SvrStarted) return 0;
    else SvrStarted = 1;

	if (ae2f_InetMk(MAKEWORD(2, 2), &Svr.m_mkdata) != 0) {
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

    SvrUnits->ID.fd = svrfd;
    new (&SvrTds->td) std::thread(SvrRes, (void*)(SvrUnits));

    for(room_t i = 0; i < MAX_ROOM_COUNT; i++) {
        SvrUnits[i + 1].Game.room = i;
        new (&SvrTds[i + 1].td) std::thread(SvrUnit, (void*)(SvrUnits + i + 1));
    }

    return 0;
}

ae2f_extern ae2f_SHAREDEXPORT
void SvrExit() {
    close(SvrUnits->ID.fd);
    SvrUnits->ID.fd = INVALID_SOCKET;

    for(size_t i = sizeof(SvrUnits) / sizeof(SvrUnits[0]) - 1; i != -1; i--) {
        SvrTds[i].td.join();
        SvrTds[i].td.~thread();
    }

    ae2f_InetDel();
}