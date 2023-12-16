using System;
using ClassiCube;

namespace ClassiCube
{
	public static partial class Block
	{
		public static bool IsLiquid(int id) {
			return GetIsLiquid(id) > 0;
		}
	}
	public static partial class Camera
	{
		public static bool IsThird {
			get { return GetIsThird() > 0; }
		}
		public static bool IsSmooth {
			get { return GetIsSmooth() > 0; }
		}	
	}
	public static partial class Chat
	{
		public static void Add(object obj) {
			Add(obj.ToString());
		}
		public static void Add(string format, params object[] a) {
			Add(string.Format(format, a));
		}
		public static void AddOf(object obj, int msgType) {
			AddOf(obj.ToString(), msgType);
		}
		public static void AddOf(int msgType, string format, params object[] a) {
			AddOf(string.Format(format, a), msgType);
		}
		public static void Send(string msg, bool logUsage) {
			int log = 0;
			if (logUsage) log = 1;
			Send(msg,log);
		}
		public static void Send(object obj, bool logUsage) {
			Send(obj.ToString(), logUsage);
		}
		public static void Send(bool logUsage, string format, params object[] a) {
			Chat.Send(string.Format(format, a), logUsage);
		}
	}
	public static partial class Server
	{
		public static bool IsSinglePlayer {
			get { return GetIsSingleplayer() > 0; }
		}
	}
	public static partial class World
	{
		public static bool PhysicsEnabled {
			get { return GetPhysicsEnabled() > 0; }
		}
	}
	public static partial class Platform
	{
		public static bool File_Exists(string path) {
			return GetFile_Exists(path) > 0;
		}
	}
}
