using System;
using System.Runtime.InteropServices;



namespace Core.Net
{
    /// <summary>
    /// This works as singleton itself automatically.
    /// </summary>
    public class Sock
    {
        /// <summary>
        /// Creates new network socket. <br/>
        /// This will make socket possible to link with another process.
        /// </summary>
        /// <returns></returns>
        [DllImport("libCli", CharSet = CharSet.Ansi)]
        public static extern int SockOpen();

        /// <summary>
        /// Close the socket.
        /// </summary>
        /// <param name="a"></param>
        [DllImport("libCli", CharSet = CharSet.Ansi)]
        public static extern void SockClose(int a);

        /// <summary>
        /// Socket's value is not meant to be mutable. <br/>
        /// So we are making it read-only.
        /// </summary>
        public readonly int fd;


        public Sock()
        {
            this.fd = SockOpen();
        }

        ~Sock()
        {
            SockClose(this.fd);
        }
    }
}