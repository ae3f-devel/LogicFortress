#include "./Player.h"

#if SERVER
#define __IsPlayerNull(p) ((p)->m_sock == INVALID_SOCKET)
#endif