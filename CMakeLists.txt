cmake_minimum_required(VERSION 3.20)

option(ae2f_IS_SHARED	"DLL EXPORT"	ON)


set(MAX_ROOM_COUNT              20)
set(MAX_ROOM_PLAYER_COUNT       6)
set(MAX_ROOM_SPECTATOR_COUNT    2)

set(MAX_ROOM_NAME_COUNT         30)
set(MAX_ROOM_PW                 30)

set(MAX_PLAYER_NAME_COUNT       32)
set(DEBUG                       1)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Plugin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Plugin)

set(player_t    unsigned)
set(room_t      unsigned)
set(sockaddrsz  16)

add_subdirectory(Bare)

configure_file(
    ${PROJECT_SOURCE_DIR}/Bare/auto/cs/SockAddrSz.cs 
    ${PROJECT_SOURCE_DIR}/Assets/Scripts/Core/Net/SockAddrSz.auto.cs
    )
    