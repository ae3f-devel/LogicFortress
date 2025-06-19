using System;
using System.Runtime.InteropServices;
using Unity.VisualScripting;
using UnityEditor.EditorTools;
using UnityEngine;

namespace Tests
{
    unsafe internal class Logger
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void LogCallback([MarshalAs(UnmanagedType.LPStr)] string msg);

        [DllImport("libCore", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        private static extern void SetTestLogger(LogCallback callback);

        private static void DebugLog([MarshalAs(UnmanagedType.LPStr)] string a)
        {
            Debug.Log(a);
        }

        internal static void AssignDebugLog()
        {
            try
            {
                LogCallback callback = DebugLog;
                SetTestLogger(callback);
                GC.KeepAlive(callback);
            }
            catch (Exception ex)
            {
                Debug.LogError($"Failed to assign debug log callback: {ex.Message}");
            }
        }
    }   
}
