using System.Text;

using cRoom = Core.Room;

namespace Wrap
{
    unsafe public readonly struct Room
    {
        public readonly cRoom r;

        public Room(cRoom r)
        {
            this.r = r;
        }

        public Room(Room r)
        {
            this.r = r.r;
        }

        public string name
        {
            get
            {
                StringBuilder builder = new StringBuilder(cRoom.MAX_ROOM_NAME_COUNT);
                for (int i = 0; i < cRoom.MAX_ROOM_NAME_COUNT; i++)
                {
                    builder[i] = (char)r.m_Name[i];
                }

                return builder.ToString();
            }
        }
    }
}