using System;
using System.Runtime.InteropServices;
using Core;

namespace Core.Net
{
    /** @brief Client */
    public class Cli
    {

        /// <summary>
        /// Request a server either to... <br/>
        /// - Make a room <br/>
        /// - Connect to a room <br/>
        /// - Verify that you are in the room <br/>
        /// - Disconnect from the room
        /// 
        /// </summary>
        /// <param name="svrsock">[sock_t] Server socket</param>
        /// <param name="svraddr">Server address.</param>
        /// 
        /// <param name="room">
        /// [room_t] <br/>
        /// Wanted room number. <br/>
        /// <br/>
        /// [Special Number: -1]: Switch <br/>
        /// When you are offline and you pass -1 here, you will make new room. <br/>
        /// When you are currently in a room and you pass -1 here, you will be offline. 
        /// </param>
        /// 
        /// <param name="retroom">
        /// [room_t] <br/>
        /// Result room number. <br/>
        /// This will be returned room number that you are currently in online state. <br/>
        /// 
        /// [Special Number: -1]: Invalid 
        /// </param>
        /// <param name="name">
        /// [Optional] <br/>
        /// If you are making a new room, your room name displayed on Lobby, <br/>
        /// If this is null, you are willing to make a "random match". <br/>
        /// 
        /// </param>
        /// <param name="pw">
        /// [Optional] <br/>
        /// If you are making a new room, this will be new password  <br/>
        /// If you are connecting to existing ones, this will be 
        /// 
        /// </param>
        /// <param name="clientname">
        /// Character name after getting in room [will be displayed
        /// ]</param>
        [DllImport("libCli", CharSet = CharSet.Ansi)]
        public static extern void ReqRoomLobby(
            int svrsock, in SockAddr svraddr,
            uint room, out uint retroom,
            [MarshalAs(UnmanagedType.LPStr)] string name,
            [MarshalAs(UnmanagedType.LPStr)] string pw,
            [MarshalAs(UnmanagedType.LPStr)] string clientname
        );

        public static void ReqRoomJoin(
            int svrsock, in SockAddr svraddr, uint room, out uint retroom,
            [MarshalAs(UnmanagedType.LPStr)] string pw,
            [MarshalAs(UnmanagedType.LPStr)] string clientname
        )
        {
            ReqRoomLobby(
                svrsock, svraddr, room,
                out retroom, null, pw, clientname);
        }

        public static void ReqRoomNewMatch(
            int svrsock, in SockAddr svraddr, out uint retroom,
            [MarshalAs(UnmanagedType.LPStr)] string clientname
            )
        {
            ReqRoomLobby(
                svrsock, svraddr, uint.MaxValue,
                out retroom, null, null, clientname
            );
        }

        public static void ReqRoomNewCustom(
            int svrsock, in SockAddr svraddr, out uint retroom,
            [MarshalAs(UnmanagedType.LPStr)] string name,
            [MarshalAs(UnmanagedType.LPStr)] string pw,
            [MarshalAs(UnmanagedType.LPStr)] string clientname
        )
        {
            if (name == null)
                throw new Exception("[ReqRoomNewCustom] name cannot be null.");

            ReqRoomLobby(
                svrsock, svraddr, uint.MaxValue,
                out retroom, name, pw, clientname
            );
        }

        [DllImport("libCli", CharSet = CharSet.Ansi)]
        public unsafe static extern void ReqRoomShow(
            int svrsock, in SockAddr svraddr
            , uint roompad, uint roomcount, _Room* retroom
            , out uint retcount
        );
    }
}