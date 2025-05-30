#include "./Player.h"

#if SERVER
#include <string.h>

#define __IsPlayerNull(p) ((p)->m_sock == INVALID_SOCKET)
#define __SetPlayerOffline(addr, retidx) \
for(*(retidx) = 0; *(retidx) < MAX_GLOBAL_PLAYER_COUNT; (*(retidx))++) { \
    if(ae2f_reinterpret_cast(const sockaddr_internal_t*, &Players[*(retidx)].m_addr)) {  \
        Players[*(retidx)].m_sock = INVALID_SOCKET; \
        memset(&Players[*(retidx)].m_addr, 0, sizeof(sockaddr_internal_t)); \
        break; \
    } \
}

#endif