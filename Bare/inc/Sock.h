#ifndef Sock_h
#define Sock_h

#include <ae2f/Inet.h>

#if _WIN32
#include <ws2tcpip.h>
#endif

typedef ae2f_InetSock       sock_t;
typedef struct sockaddr_in  sockaddr_internal_t;
typedef struct sockaddr     sockaddr_t;    
typedef socklen_t socklen_t;

#define sockaddr_internal_check(a, b) \
((a)->sin_family == (b)->sin_family && \
(a)->sin_addr.s_addr == (b)->sin_addr.s_addr && \
(a)->sin_port == (b)->sin_port)

#endif