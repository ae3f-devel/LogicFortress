using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using Unity.VisualScripting;
using cRoom = Core.Room;

namespace Wrap
{
    unsafe public struct RoomIter : IEnumerator<Room>
    {
        readonly cRoom[] r;
        int  idx;

        public int Index => idx;

        public RoomIter(cRoom[] r, int idx = 0)
        {
            Debug.WriteLine("Hello");

            this.r = r;

            if (r.Length <= idx)
                throw new System.Exception("Idx is too big");

            this.idx = idx;
        }

        public Room Current => new Room(r[idx]);

        object IEnumerator.Current => Current;

        public void Dispose() {}

        public bool MoveNext()
        {
            idx++;

            if (r.Length <= idx)
            {
                idx--;
                return false;
            }

            Debug.WriteLine("MoveNext");

            return true;
        }

        public void Reset()
        {
            idx = 0;

            return;
        }
    }

    unsafe public readonly struct RoomArr : IEnumerable<Room>
    {
        public readonly cRoom[] r;

        public RoomArr(cRoom[] r)
        {
            this.r = r;
        }

        public RoomArr(RoomArr r)
        {
            this.r = r.r;
        }

        public RoomArr(int count)
        {
            this.r = new cRoom[count];
        }

        public IEnumerator GetEnumerator()
        {
            return new RoomIter(r);
        }

        IEnumerator<Room> IEnumerable<Room>.GetEnumerator()
        {
            Debug.WriteLine("Get enumerator");
            return new RoomIter(r);
        }
    }

    unsafe public readonly struct Room 
    {
        public readonly cRoom r;
        public Room(cRoom r)
        {
            Debug.WriteLine("Casting is happening");
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
                fixed (sbyte* name = r.m_Name) {
                    return Marshal.PtrToStringAnsi((nint)name);
                }
            }
        }
    }
}