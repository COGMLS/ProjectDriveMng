using System;
using DotNetConsoleExtensions;

namespace ProjectDriveConsole
{
	internal class Program
	{
		static void Main(string[] args)
		{
			DrawConsole.DrawBorder(15, 1);

			Console.WriteLine("Project Drive Console Manager");

			DrawConsole.Move2OutsideConsoleBorder();
		}
	}
}
