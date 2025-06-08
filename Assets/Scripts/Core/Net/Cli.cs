using System;
using System.Runtime.InteropServices;

namespace Core.Net
{

    /// <summary>
    /// Ancient library call from `Bare`.
    /// This has no ability to 
    /// </summary>
    internal static class Cli
    {
        public const uint INVALID = uint.MaxValue;
        public const uint OFFLINE = uint.MaxValue;
        public const uint UNSPECIFIED = uint.MaxValue;

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
        /// <param name="retglobplayer">
        /// [globplayer_t] <br/>
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
        /// If you are connecting to existing ones, this will be password attempt. <br/>
        /// This could be null, and equals to "".
        /// 
        /// </param>
        /// <param name="clientname">
        /// Character name after getting in room will be displayed
        /// </param>
        [DllImport("libCli", CharSet = CharSet.Ansi)]
        internal static extern void ReqRoomLobby(
            int svrsock, in SockAddr svraddr,
            uint room, out uint retglobplayer,
            [MarshalAs(UnmanagedType.LPStr)] string name,
            [MarshalAs(UnmanagedType.LPStr)] string pw,
            [MarshalAs(UnmanagedType.LPStr)] string clientname
        );

        /// <summary>
        /// Requests server a shared room information.
        /// </summary>
        /// <param name="svrsock"></param>
        /// <param name="svraddr"></param>
        /// <param name="roompad">
        /// Index of room to start.
        /// </param>
        /// <param name="roomcount">
        /// Count of room for request
        /// </param>
        /// <param name="retroom">
        /// A pointer where rooms be store.
        /// </param>
        /// <param name="retcount">
        /// Actual count of rooms successfully fetched.
        /// </param>
        [DllImport("libCli", CharSet = CharSet.Ansi)]
        internal unsafe static extern void ReqRoomShow(
            int svrsock, in SockAddr svraddr
            , uint roompad, uint roomcount, Room* retroom
            , out uint retcount
        );
    }
}
