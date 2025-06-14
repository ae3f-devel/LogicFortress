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
set(MAX_SKILL_COUNT		3)

# DEBUG
set(DEBUG                       1)

# OUTPUT FOR PLUGIN
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Plugins)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/Plugins)

# TYPES
set(player_t        	unsigned)
set(globplayer_t   	unsigned)
set(room_t         	unsigned)
set(character_t    	"unsigned char")
set(skillid_t    	"unsigned char")

set(player_cs_t       	uint)
set(globplayer_cs_t   	uint)
set(room_cs_t         	uint)
set(character_cs_t    	byte)
set(skillid_t   	byte)

set(sockaddrsz  16)

# TEST PORT VAL
set(TEST_PORT           6767)

execute_process(
	COMMAND git clone https://github.com/ae3f-devel/Bare Bare
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

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
    ${PROJECT_SOURCE_DIR}/Bare/auto/cs/Player.cs 
    ${PROJECT_SOURCE_DIR}/Assets/Scripts/Core/Player.auto.cs
    )

configure_file(
    ${PROJECT_SOURCE_DIR}/Bare/auto/cs/TestPort.cs 
    ${PROJECT_SOURCE_DIR}/Assets/Scripts/Test/Port.auto.cs
    )

if(WIN32)
	message("[WINDOWS DETECTED] libgcc will be static")
    	target_compile_options(libCli PRIVATE -static-libgcc -static-libstdc++)
    	target_compile_options(libCli PRIVATE -static-libgcc -static-libstdc++)
     	target_compile_options(libSvrUDP PRIVATE -static-libgcc -static-libstdc++)
      	file(
       		COPY "C:/mingw64/bin/libgcc_s_seh-1.dll" 
	 	DESTINATION "${PROJECT_SOURCE_DIR}/Assets/Plugins/"
   	)
      	file(
       		COPY "C:/mingw64/bin/libstdc++-6.dll" 
		DESTINATION "${PROJECT_SOURCE_DIR}/Assets/Plugins/"
   	)
      	file(
       		COPY "C:/mingw64/bin/libwinpthread-1.dll" 
	 	DESTINATION "${PROJECT_SOURCE_DIR}/Assets/Plugins/"
   	)
endif()
