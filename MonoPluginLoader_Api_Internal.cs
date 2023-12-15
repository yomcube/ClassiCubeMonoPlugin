using System;
using System.Runtime.CompilerServices;

namespace ClassiCube {
	public static partial class Block {
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int Parse(string value);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetIsLiquid(int id);
	}
	public static partial class Camera {
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetFov();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetIsThird();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetX();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetY();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetZ();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetYaw();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetPitch();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetIsSmooth();
	}
	public static partial class Chat {
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void Add(string msg);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void AddOf(string msg, int msgType);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void Send(string msg, int logUsage);
	}
	public static partial class Env {
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void SetEdgeBlock(int id);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void SetEdgeHeight(int height);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void SetSidesBlock(int id);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void SetSidesOffset(int offset);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void SetCloudsHeight(int height);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void SetCloudsSpeed(float speed);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void SetWeather(int weather);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void SetWeatherSpeed(float speed);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void SetWeatherFade(float rate);
	}
	public static partial class Game {
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void SetBlock(int x, int y, int z, int id);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void ChangeBlock(int x, int y, int z, int id);
	}
	public static partial class Inventory {
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetSelected();
	}
	public static partial class Player {
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetReach();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetX();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetY();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetZ();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetYaw();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetPitch();
	}
	public static partial class Server {
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static string GetMotd();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static string GetName();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static string GetAppName();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static string GetAddress();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetPort();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void SetAppName(string name);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetIsSingleplayer();
	}
	public static partial class Tablist {
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static string GetPlayer(int id);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static string GetName(int id);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static string GetGroup(int id);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetRank(int id);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void Remove(int id);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void Set(int id, string player, string name, string group, int groupRank);
	}
	public static partial class Window {
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void SetTitle(string title);
	}
	public static partial class World {
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetWidth();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetHeight();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetLength();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetBlock(int x, int y, int z);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void NewMap();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetPhysicsEnabled();
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetSeed();
	}
	public static partial class Platform {
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static void Process_Exit(int code);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int Process_StartOpen(string args);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int Directory_Create(string path);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		public extern static int GetFile_Exists(string path);
	}
}