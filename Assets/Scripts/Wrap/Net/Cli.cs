using System;
using System.Runtime.InteropServices;
using Core;
using Core.Net;
using cCli = Core.Net.Cli;

namespace Wrap.Net
{
    /// <summary>
    /// 
    /// </summary>
    public struct Cli
    {
        public Sock sock;
        public SockAddr addr;

        public Cli([MarshalAs(UnmanagedType.LPStr)] string ip, ushort port)
        {
            addr = new SockAddr(ip, port);
            sock = new Sock();
        }

        public globplayer_t ReqRoomJoin(
            uint room,
            [MarshalAs(UnmanagedType.LPStr)] string pw,
            [MarshalAs(UnmanagedType.LPStr)] string clientname
        )
        {
            globplayer_t retglobplayer;
            cCli.ReqRoomLobby(
                sock.fd, addr, room,
                out retglobplayer.a,
                null, pw, clientname
                );

            return retglobplayer;
        }

        public globplayer_t ReqRoomExit()
        {
            globplayer_t ret;
            cCli.ReqRoomLobby(
                sock.fd, addr, cCli.OFFLINE,
                out ret.a, null, null, ""
            );
            return ret;
        }

        public globplayer_t ReqRoomNewMatch(
            [MarshalAs(UnmanagedType.LPStr)] string clientname
            )
        {
            globplayer_t retglobplayer;

            cCli.ReqRoomLobby(
                sock.fd, in addr, cCli.UNSPECIFIED,
                out retglobplayer.a, null, null, clientname
            );
            return retglobplayer;
        }

        public globplayer_t ReqRoomNewCustom(
            [MarshalAs(UnmanagedType.LPStr)] string name,
            [MarshalAs(UnmanagedType.LPStr)] string pw,
            [MarshalAs(UnmanagedType.LPStr)] string clientname
        )
        {
            globplayer_t retglobplayer;
            if (name == null)
                throw new Exception("[ReqRoomNewCustom] name cannot be null.");

            cCli.ReqRoomLobby(
                this.sock.fd, addr, uint.MaxValue,
                out retglobplayer.a, name, pw, clientname
            );

            return retglobplayer;
        }
    }
}