cmake_minimum_required(VERSION 3.20)
enable_testing()

option(ae2f_IS_SHARED	"DLL EXPORT"	ON)
option(ae2f_TEST	""	                ON)

# MAX
set(MAX_ROOM_COUNT              10)
set(MAX_ROOM_PLAYER_COUNT       6)
set(MAX_ROOM_SPECTATOR_COUNT    2)

set(MAX_ROOM_NAME_COUNT         30)
set(MAX_ROOM_PW                 30)

set(MAX_PLAYER_NAME_COUNT       32)

# DEBUG
set(DEBUG                       1)

# OUTPUT FOR PLUGIN
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Plugins/${CMAKE_SYSTEM_PROCESSOR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Plugins/${CMAKE_SYSTEM_PROCESSOR})

# TYPES
set(player_t    unsigned)
set(room_t      unsigned)
set(sockaddrsz  16)

# TEST PORT VAL
set(TEST_PORT           9000)

add_subdirectory(Bare)

configure_file(
    ${PROJECT_SOURCE_DIR}/Bare/auto/cs/SockAddrSz.cs 
    ${PROJECT_SOURCE_DIR}/Assets/Scripts/Core/Net/SockAddrSz.auto.cs
    )

configure_file(
    ${PROJECT_SOURCE_DIR}/Bare/auto/cs/Room.cs 
    ${PROJECT_SOURCE_DIR}/Assets/Scripts/Core/Room.auto.cs
    )

configure_file(
    ${PROJECT_SOURCE_DIR}/Bare/auto/cs/TestPort.cs 
    ${PROJECT_SOURCE_DIR}/Assets/Scripts/Test/Port.auto.cs
    )