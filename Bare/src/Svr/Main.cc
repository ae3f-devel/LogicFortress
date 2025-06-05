#define SERVER 1

#include "./SvrMain.h"
#include <Sock.imp.h>

#include <cstdlib>
#include <new>

ae2f_extern ae2f_SHAREDEXPORT _SvrUnit SvrUnits[MAX_ROOM_COUNT + 1] = {};

ae2f_extern ae2f_SHAREDEXPORT _SvrUnitIDHandle SvrTds[MAX_ROOM_COUNT + 1] = {};

ae2f_extern ae2f_SHAREDCALL void SvrUnit(void *);
ae2f_extern ae2f_SHAREDCALL void SvrRes(void *);

static unsigned SvrStarted = 0;

ae2f_extern ae2f_SHAREDCALL void SvrExit();

/**
 * @brief
 * @param port
 * @returns 0 when succeed.
 */
ae2f_extern ae2f_SHAREDEXPORT int SvrMain(unsigned short port) {
  if (SvrStarted)
    return 0;
  else
    SvrStarted = 1;

  {
    ae2f_InetMkData mkdata;
    if (ae2f_InetMk(MAKEWORD(2, 2), &mkdata) != 0) {
      return 1;
    }
  }

  sock_t svrfd = 0;
  union {
    sockaddr_t addr;
    sockaddr_internal_t in[1];
  } svraddr;

  if ((svrfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {

    close(svrfd);
    return 1;
  }

  __SockAddrMkVerbose(svraddr.in, INADDR_ANY, port);

  int a;
  if ((a = bind(svrfd, &svraddr.addr, sizeof(sockaddr_t)))) {
    close(svrfd);
    return (a);
  }

  SvrUnits->ID.fd = svrfd;
  new (&SvrTds->td) std::thread(SvrRes, (void *)(SvrUnits));

  for (room_t i = 0; i < MAX_ROOM_COUNT; i++) {
    SvrUnits[i + 1].Game.room = i;
    SvrUnits[i + 1].ID.fd = svrfd;
    new (&SvrTds[i + 1].td) std::thread(SvrUnit, (void *)(SvrUnits + i + 1));
  }

  /** Waiting for thread be actually started. */
  RoomFlags[MAX_ROOM_COUNT] = 0;
  __ae2f_Wait(&RoomFlags[MAX_ROOM_COUNT], 0);

  return 0;
}

#include "./SvrMain.h"

ae2f_extern ae2f_SHAREDEXPORT void SvrExit() {
  close(SvrUnits->ID.fd);
  

  for (size_t i = sizeof(SvrUnits) / sizeof(SvrUnits[0]) - 1; i != -1; i--) {
    SvrUnits[i].ID.fd = INVALID_SOCKET;
    if(i) {
      RoomFlags[i - 1] = 2; /* Changing roomflags to stop waiting */
      __ae2f_WakeSingle(RoomFlags + i - 1); /* notify the memory */
    }

    SvrTds[i].td.join();
    SvrTds[i].td.~thread();

    if(i == 0) break;
  }

  ae2f_InetDel();
}
