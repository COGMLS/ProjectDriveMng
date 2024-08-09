using System;

namespace DotNetConsoleExtensions
{
	public struct MenuMessage
	{
		public readonly string[] message;
		public readonly ConsoleColor foregroundColor;
		public readonly ConsoleColor backgroundColor;

		public MenuMessage(string[] message)
		{
			this.message = message;
			this.foregroundColor = Console.ForegroundColor;
			this.backgroundColor = Console.BackgroundColor;
		}

		public MenuMessage(string[] message, ConsoleColor foregroundColor)
		{
			this.message = message;
			this.foregroundColor = foregroundColor;
			this.backgroundColor = Console.BackgroundColor;
		}

		public MenuMessage(string[] message, ConsoleColor foregroundColor, ConsoleColor backgroundColor)
		{
			this.message = message;
			this.foregroundColor = foregroundColor;
			this.backgroundColor = backgroundColor;
		}

		public void Write()
		{
			ConsoleColor actualForegroundColor = Console.ForegroundColor;
			ConsoleColor actualBackgroundColor = Console.BackgroundColor;

			string tmp = "";

			for (int i = 0; i < this.message.Length; i++)
			{
				tmp += this.message[i];
			}

			Console.ForegroundColor = actualForegroundColor;
			Console.BackgroundColor = actualBackgroundColor;
		}

		public void WriteLine()
		{
			ConsoleColor actualForegroundColor = Console.ForegroundColor;
			ConsoleColor actualBackgroundColor = Console.BackgroundColor;

			string tmp = "";

			for (int i = 0; i < this.message.Length; i++)
			{
				if (i != 0 && i < this.message.Length - 1)
				{
					tmp += "\n";
				}

				tmp += this.message[i];
			}

			Console.ForegroundColor = actualForegroundColor;
			Console.BackgroundColor = actualBackgroundColor;
		}
	}
}
