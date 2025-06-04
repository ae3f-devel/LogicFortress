#include <stdio.h>
#include <Dbg.h>
#include <Room.imp.h>
#include <Sock.h>
#include <Sock.imp.h>

#include "../port.auto.h"

static inline void PrtnRoom(Room* a) {
    printf("ROOM:\n");
    if(!a) puts("(nil)");

    printf("MEMBER: %d\n",     a->m_member);
    if(a->m_Name)
        printf("NAME: %s\n",     a->m_Name);
    else
        puts("NAME: (nil)");

    printf("STARTED: %d\n",     a->m_started);
}

int main() {
    ae2f_InetMkData data;
    ae2f_InetMk(MAKEWORD(2, 2), &data);

    sock_t sock = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_internal_t in[1];
    __SockAddrMk(in, "58.235.181.91", TEST_PORT);
    room_t r; Room ro[5];

    ReqRoomShow(sock, (sockaddr_t*)in, 0, 5, ro, &r);
    printf("%d\n", r);

    for(size_t i = 0; i < r; i++) {
        PrtnRoom(ro + i);
    }

    close(sock);
    ae2f_InetDel();
    return 0;
}