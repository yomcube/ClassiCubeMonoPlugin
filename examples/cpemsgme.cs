using System;
using ClassiCube;

namespace ClassiCube
{
	public class CpeMsgMePlugin : Plugin
	{
		public override string Name { get { return "CpeMsgMePlugin"; } }
		public override int PluginApiVersion { get { return 1; } }
		public override void Run() {
			Command.Register(new CpeMsgMeCommand());
		}
		
		public class CpeMsgMeCommand : Command {
			public override string Name { get { return "cpemsgme"; } }
			public override string Help { get {
				return  "&a/client monocmd cpemsgme [type] [message]\n" +
						"&eMessages yourself using the specified message type.";
			} }
			public override void Execute(string args) {
				if (args.Length == 0 || args == null) return;
				
				string[] split = args.Split(new char[] {' '}, 2);
				if (split.Length != 2) {
					Chat.Add("Could not parse arguments.");
				}
				if (!int.TryParse(split[0], out int i)) {
					Chat.Add("Could not parse {0} as an integer.", split[0]);
					return;
				}
				bool isValidType = (i >= 0 && i <= 3) || (i >= 11 && i <= 13) ||
					(i >= 100 && i <= 102) || (i == 256 || i == 257) || (i == 360 || i == 361);
				if (!isValidType) {
					Chat.Add("{0} is not a valid message type.", i);
					return;
				}
				Chat.AddOf(split[1], i);
			}
		}
	}
}