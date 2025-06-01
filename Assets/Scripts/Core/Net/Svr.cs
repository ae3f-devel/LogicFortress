using System;
using System.Runtime.InteropServices;
using Core;
using Mono.Cecil.Cil;

namespace Core.Net
{
    /** @brief Client */
    public class Svr
    {
        [DllImport("liblibSvr")]
        public static extern int SvrMain(ushort port);

        [DllImport("liblibSvr")]
        public static extern int SvrExit();

        /// <summary>
        /// Singleton-Constructor.
        /// </summary>
        /// <param name="port"></param>
        /// <param name="c">When 0 it succeed.</param>
        public Svr(ushort port, out int c) { c = SvrMain(port); }
        ~Svr() { SvrExit(); }
    }
}