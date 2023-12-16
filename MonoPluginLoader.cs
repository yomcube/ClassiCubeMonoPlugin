using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using ClassiCube;

namespace ClassiCube {
	//
	// Plugin
	//
	public abstract class Plugin
	{
		public abstract string Name { get; }
		public abstract int PluginApiVersion { get; }
		public abstract void Run();
	}
	
	//
	// Events
	//
	public static class Events
	{
		public static event EventHandler Free      = delegate {};
		public static event EventHandler Reset     = delegate {};
		public static event EventHandler NewMap    = delegate {};
		public static event EventHandler MapLoaded = delegate {};
		
		public static void RaiseFree      () { Free      (null, EventArgs.Empty); }
		public static void RaiseReset     () { Reset     (null, EventArgs.Empty); }
		public static void RaiseNewMap    () { NewMap    (null, EventArgs.Empty); }
		public static void RaiseMapLoaded () { MapLoaded (null, EventArgs.Empty); }
	}
	
	//
	// Utils
	//
	public static class Utils
	{
		public const int STRLEN = 80;
		// https://stackoverflow.com/a/3008775
		public static IEnumerable<string> SplitByLength(this string str)
		{
			if (str.Length <= STRLEN) {
				yield return str;
				yield break;
			}
			for (int index = 0; index < str.Length; index += STRLEN)
				yield return str.Substring(index, Math.Min(STRLEN, str.Length - index));
		}
		public static void DescribeError(this Exception e, string msg = null)
		{
			if (msg != null) Chat.Add("&cError when " + msg);
			Chat.Add("&c" + e.GetType());
			foreach (string s in e.Message.SplitByLength())
				Chat.Add("&c" + s);
				
			string[] stackTraceLines = e.StackTrace.Split('\n');
			foreach (string s in stackTraceLines) {
				foreach (string st in s.SplitByLength())
					Chat.Add("&c" + st);
				
			}
		}
	}
	
	//
	// PluginLoader
	//
	public static class PluginLoader
	{
		public static List<Plugin> plugins = new List<Plugin>();
		
		// Modified from MCGalaxy
		public static List<T> LoadTypes<T>(Assembly lib) {
			List<T> instances = new List<T>();
			foreach (Type t in lib.GetTypes()) {
				if (t.IsAbstract || t.IsInterface || !t.IsSubclassOf(typeof(T))) continue;
				object instance = Activator.CreateInstance(t);
				if (instance == null) {
					Chat.Add("&cPlugin '" + t.Name + "' could not be loaded");
					throw new BadImageFormatException();
				}
				instances.Add((T)instance);
			}
			return instances;
		}
		public static void FileCallback (string filename)
		{
			try {
				// TODO: remove debug stuff
				if (filename == null) { Chat.Add("filename == null"); return; }
				// Workaround to prevent exceptions from using filename.EndsWith(".dll")
				// TODO: remove debug stuff
				Chat.Add(filename);
				bool isDll =
					filename.Length > 3 &&
					filename[filename.Length - 4] == '.' &&
					filename[filename.Length - 3] == 'd' &&
					filename[filename.Length - 2] == 'l' &&
					filename[filename.Length - 1] == 'l';
				// TODO: remove debug stuff
				Chat.Add(isDll);
				if (!isDll)
					return;
				Assembly a = Assembly.LoadFile(filename);
				try {
					plugins = LoadTypes<Plugin>(a);
				} catch (Exception e) {
					e.DescribeError("loading plugin from " + filename);
				}
				foreach (Plugin p in plugins) {
					try {
						p.Run();
					} catch (Exception e) {
						e.DescribeError("running plugin " + p.Name);
					}
				}
			} catch (Exception e) {
				e.DescribeError();
			}
		}
	}
}
