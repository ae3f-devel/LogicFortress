namespace Core
{
    public unsafe struct _Room
    {
        public fixed char m_Name[@MAX_ROOM_NAME_COUNT@];
        public char m_started;
        public nuint m_member;
    }   
}