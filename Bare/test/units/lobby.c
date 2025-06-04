#include <stdio.h>
#include <Dbg.h>
#include <Room.imp.h>
#include <Sock.h>
#include <Sock.imp.h>

#include "../port.auto.h"

int main() {
    ae2f_InetMkData data;
    ae2f_InetMk(MAKEWORD(2, 2), &data);

    sock_t sock = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_internal_t in[1];
    __SockAddrMk(in, "58.235.181.91", TEST_PORT);
    room_t r;

    ReqRoomLobby(sock, (sockaddr_t*)in, -1, &r, "FEARNOT", NULL, "Playername");

    printf("%d\n", r);

    close(sock);
    ae2f_InetDel();
    return 0;
}