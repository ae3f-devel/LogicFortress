using System.Runtime.InteropServices;

namespace Core.Net
{
    public struct SockAddr
    {
        SockAddrSz sz;
        
        [DllImport("liblibCli", CharSet = CharSet.Ansi)]
        public static extern void SockAddrMk(
            out SockAddr sock,
            [MarshalAs(UnmanagedType.LPStr)] string ip,
            ushort port
        );

        /// <summary>
        /// IP and Port to make socket address buffer.
        /// </summary>
        /// <param name="ip"></param>
        /// <param name="port"></param>
        public SockAddr([MarshalAs(UnmanagedType.LPStr)] string ip, ushort port)
        {
            SockAddrMk(out this, ip, port);
        }
    }
}