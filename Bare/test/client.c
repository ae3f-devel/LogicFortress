#include <stdio.h>
#include <Dbg.h>
#include <Room.imp.h>
#include <Sock.h>
#include <Sock.imp.h>

int main() {
    ae2f_InetMkData data;
    ae2f_InetMk(MAKEWORD(2, 2), &data);

    sock_t sock = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_internal_t in[1];
    __SockAddrMk(in, "127.0.0.1", 8080);
    room_t r; Room ro[5];

    ReqRoomShow(sock, (sockaddr_t*)in, 0, 5, ro, &r);

    printf("%d\n", r);

    close(sock);
    ae2f_InetDel();
    return 0;
}