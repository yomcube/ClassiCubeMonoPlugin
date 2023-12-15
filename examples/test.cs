using System;
using System.Runtime.CompilerServices;
using System.Threading;
using ClassiCube;

namespace ClassiCube
{	
	public class TestPlugin : Plugin
	{	
		public override string Name { get { return "TestPlugin"; } }
		public override int PluginApiVersion { get { return 1; } }
		public override void Run()
		{
			Chat.Add("Hello World from TestPlugin");
			Events.Reset += OnReset;
			Events.MapLoaded += OnMapLoaded;
		}
		public void OnReset(object sender, EventArgs e) {
			Chat.Add("TestPlugin reset");
		} 
		public void OnMapLoaded(object sender, EventArgs e) {
			Chat.Add("TestPlugin maploaded");
			Chat.Add(World.GetWidth() + " " + World.GetHeight() + " " + World.GetLength());
			Env.SetWeather(2);
			Chat.Add(Block.IsLiquid(1/*Stone*/));
		}
	}
}