#include "./Sock.h"
#include <string.h>

#define __SockAddrMkVerbose(addr, ip, port)  \
    if(addr) { \
        memset(addr, 0, sizeof(sockaddr_internal_t)); \
        if(ip) (addr)->sin_addr.s_addr = ip; \
        (addr)->sin_family = AF_INET; \
        (addr)->sin_port = port; \
    }

#define __SockAddrMk(addr, ip, port)  \
    __SockAddrMkVerbose(addr, inet_addr(ip), port)