#include <Sock.h>
#include <stddef.h>
#include <string.h>

ae2f_SHAREDEXPORT
size_t SockAddrSz() { return sizeof(sockaddr_internal_t); }

ae2f_SHAREDEXPORT
void SockAddrMk(sockaddr_internal_t* addr, const char* ip, unsigned short port) {
    if(addr) {
        memset(addr, 0, sizeof(sockaddr_internal_t));
        if(ip) addr->sin_addr.s_addr = inet_addr(ip);
        addr->sin_family = AF_INET;
        addr->sin_port = port;
    }
}