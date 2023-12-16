using System;
using System.Collections.Generic;
using ClassiCube;

namespace ClassiCube
{
	public abstract class Command {
		public abstract string   Name             { get                                ; }
		public virtual  string   Help             { get { return "No help available."; } }
		public virtual  bool     SingleplayerOnly { get { return        false        ; } }
		public abstract void     Execute(string args);
		
		public static Dictionary<string,Command> Commands = new Dictionary<string,Command>(); 
		
		public static void Register(Command cmd)
		{
			Commands.Add(cmd.Name, cmd);
		}
		public static void ListCommands()
		{
			if (Commands.Count == 0)
			{
				Chat.Add("&eNo mono commands have been registered.");
				return;
			}
			Chat.Add("&eAvailable mono commands are:");
			foreach (KeyValuePair<string,Command> pair in Commands) {
				Chat.Add(" &e " + pair.Value.Name);
			}
		}
		public static void HandleCommand(string args)
		{
			string[] split = args.Split(new char[] {' '}, 2);
			try {
				Command c;
				try {
					c = Commands[split[0]];
				} catch (KeyNotFoundException) {
					Chat.Add("&e/client monocmd: Unrecongnised command: \"{0}\".", split[0]);
					Chat.Add("&e/client monocmd: Type &a/client monocmd &efor a list of commands.");
					return;
				}
				
				if (c.SingleplayerOnly && !Server.IsSinglePlayer) {
					Chat.Add("&e/client monocmd: \"{0}\" can only be used in singleplayer.", c.Name);
				}
				
				string cmdArgs = ""; 
				if (split.Length == 2) cmdArgs = split[1];
				c.Execute(cmdArgs);
			} catch (Exception e) {
				e.DescribeError();
			}
		}
		
		// Built-in commands
		
		public static void InitCommands() {
			Register(new HelpCommand());
		}
		
		public class HelpCommand : Command {
			public override string Name { get { return "help"; } }
			public override string Help { get {
				return  "&a/client monocmd help [command]\n" +
						"&eDisplays help for the given command.";
			} }
			public override void Execute (string args)
			{
				if (args.Length == 0 || args == null) {
					ListCommands();
					return;
				}
				Command c = null;
				try { c = Commands[args]; }
				catch (KeyNotFoundException) { Chat.Add("Unable to find command \"{0}\"", args); return; }
				
				string[] strs = new string[] { c.Help };
				try { strs = c.Help.Split('\n'); } catch {} 
				
				foreach (string s in strs)
					Chat.Add(s);
			}
		}
	}
}
