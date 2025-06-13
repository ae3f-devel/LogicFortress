
namespace Core
{
    public static unsafe class Player {
        public const int MAX_GLOBAL_PLAYER_COUNT = ((6 + 2) * 10);
    }

    public struct player_t {
        public uint a;
    }

    public struct globplayer_t {
        public uint a;

        public bool isvalid { get { return this.a != uint.MaxValue; } }

        public room_t room
        {
            get
            {
                room_t r;
                r.a = (uint)(a / Room.MAX_ROOM_MEM_COUNT);
                return r;
            }
        }

        public player_t player
        {
            get
            {
                player_t player;
                player.a = (uint)(a % Room.MAX_ROOM_MEM_COUNT);
                return player;
            }
        }
    }
}
