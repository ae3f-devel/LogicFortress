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

        public fixed sbyte m_Name[30];
        public byte m_started;
        public uint m_member;
    }

    public struct room_t {
        public uint a;
    }
}
