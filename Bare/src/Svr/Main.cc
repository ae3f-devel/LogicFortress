#define SERVER 1

#include "./SvrMain.h"
#include <Sock.imp.h>

#include <cstdlib>
#include <new>

#include "./RoomPrivate.h"
#include <ae2f/Atom.h>

#include "./PlConn.h"
#include <Patternise.h>

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
  uSockAddr svraddr;

  if ((svrfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {

    close(svrfd);
    return 1;
  }

  __SockAddrMkVerbose(&svraddr.m_in, INADDR_ANY, port);

  int a;
  if ((a = bind(svrfd, &svraddr.m_addr, SockAddrLen))) {
    close(svrfd);
    return (a);
  }

  SvrUnits->ID.fd = svrfd;
  new (&SvrTds->td) std::thread(SvrRes, (void *)(SvrUnits));

  for (globplayer_t i = 0; i < MAX_GLOBAL_PLAYER_COUNT; i++) {
    if (!(i % MAX_ROOM_MEM_COUNT)) {
      room_t j = i / MAX_ROOM_MEM_COUNT;
      SvrUnits[j + 1].Game.room = j;
      SvrUnits[j + 1].ID.fd = INVALID_SOCKET;
      new (&SvrTds[j + 1].td) std::thread(SvrUnit, (void *)(SvrUnits + j + 1));
    }

    PlConns[i].m_connected = 0;
  }

  return 0;
}

#include "./SvrMain.h"

ae2f_extern ae2f_SHAREDEXPORT void SvrExit() {
  close(SvrUnits->ID.fd);

  for (size_t i = sizeof(SvrUnits) / sizeof(SvrUnits[0]) - 1; i != -1; i--) {
    SvrUnits[i].ID.fd = INVALID_SOCKET;
    if (i) {
      RoomFlags[i - 1] = 2; /* Changing roomflags to stop waiting */
      __ae2f_WakeSingle(RoomFlags + i - 1); /* notify the memory */
    }

    SvrTds[i].td.join();
    SvrTds[i].td.~thread();

    if (i == 0)
      break;
  }

  ae2f_InetDel();
}
