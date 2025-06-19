using globplayer_t = System.UInt32;
using room_t = System.UInt32;
using player_t = System.UInt32;
using System.Runtime.InteropServices;


namespace Core
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public unsafe struct Room
    {
        public const int MAX_ROOM_NAME_COUNT = 30;
        public const int MAX_ROOM_PLAYER_COUNT = 6;
        public const int MAX_ROOM_SPECTATOR_COUNT = 2;
        public const int MAX_ROOM_COUNT = 10;
        public const int MAX_ROOM_MEM_COUNT = 6 + 2;

        internal fixed sbyte m_Name[30];
        public byte m_started;
        public System.UInt32 m_member;

        public string name
        {
            get
            {
                fixed (sbyte* _name = m_Name)
                {
                    return Marshal.PtrToStringAnsi((nint)_name);   
                }
            }
        }
    }

    public struct RoomIndex {
        public System.UInt32 a;
        public const System.UInt32 INVALID = System.UInt32.MaxValue;
    }
}
