#ifndef Sock_imp_h
#define Sock_imp_h

#include "./Sock.h"
#include <string.h>
#include "./Dbg.h"
#include "./Patternise.h"

#define __SockAddrMkVerbose(addr, ip, port)  \
    if(addr) { \
        (addr)->sin_addr.s_addr = (ip); \
        (addr)->sin_family = AF_INET; \
        (addr)->sin_port = htons(port); \
    }

#define __SockAddrMk(addr, ip, port)  \
    __SockAddrMkVerbose(addr, (ip) ? inet_addr(ip) : 0, port)

#define __uSockAddrMk(uaddr, ip, port)  \
        __SockAddrMk(&(uaddr)->m_in, ip, port)

#define __uSockAddrPrint(uaddr) \
        dbg_puts("Addr: "); \
        dbg_printf("sinaddr %llu\n", (addr)->m_in.sin_addr.s_addr); \
        dbg_printf("port %llu\n", (addr)->m_in.sin_port);

#endif