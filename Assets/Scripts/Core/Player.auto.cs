using globplayer_t = System.UInt32;
using room_t = System.UInt32;
using player_t = System.UInt32;
using System;

namespace Core
{
    public static unsafe class Player {
        public const int MAX_GLOBAL_PLAYER_COUNT = ((6 + 2) * 10);
    }

    public struct PlayerIndex {
        public System.UInt32 a;
        public const System.UInt32 INVALID = System.UInt32.MaxValue;
    }

    public struct GlobPlayerIndex {
        public System.UInt32 a;

        public const System.UInt32 INVALID =  System.UInt32.MaxValue;

        public bool isvalid { get { return this.a != INVALID; } }

        public void ThrowOnNValid()
        {
            if (a == INVALID)
                throw new Exception("room must not be invalid");
        }

        public room_t room
        {
            get
            {
                ThrowOnNValid();
                room_t r;
                r = (System.UInt32)(a / Room.MAX_ROOM_MEM_COUNT);
                return r;
            }
        }

        public player_t player
        {
            get
            {
                ThrowOnNValid();
                player_t player;
                player = (System.UInt32)(a % Room.MAX_ROOM_MEM_COUNT);
                return player;
            }
        }
    }
}
