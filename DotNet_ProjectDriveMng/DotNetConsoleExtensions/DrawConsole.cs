using System;

namespace DotNetConsoleExtensions
{
	public static class DrawConsole
	{
		/// <summary>
		/// Move the cursor to last line
		/// </summary>
		public static void Move2OutsideConsoleBorder()
		{
			Console.SetCursorPosition(Console.BufferWidth - 1, Console.BufferHeight - 1);
			Console.Write("\n");
		}

		/// <summary>
		/// Draw a border on console
		/// </summary>
		/// <param name="setCursorPosX"></param>
		/// <param name="setCursorPosY"></param>
		public static void DrawBorder(int? setCursorPosX = null, int? setCursorPosY = null)
		{
			int maxHeight = Console.BufferHeight;
			int maxWidth = Console.BufferWidth;

			int actualCursorPosX = Console.GetCursorPosition().Top;
			int actualCursosPosY = Console.GetCursorPosition().Left;

			for (int y = 0; y < maxHeight; y++)
			{
				for (int x = 0; x < maxWidth; x++)
				{
					Console.SetCursorPosition(x, y);

					// Make a complete draw on first and last console lines:
					if (y == 0 || y == maxHeight - 1)
					{
						if (x == 0 && y == 0)
						{
							Console.Write("/"); // Top Left corner (original symbol: u250F)
						}
						else if (x == maxWidth - 1 && y == 0)
						{
							Console.Write("\\");    // Top right corner (original symbol: u2513)
						}
						else if (x == 0 && y == maxHeight - 1)
						{
							Console.Write("\\");    // Bottom left corner (original symbol: u2517)
						}
						else if (x == maxWidth - 1 && y == maxHeight - 1)
						{
							Console.Write("/"); // Bottom right corner (original symbol: u251B)
						}
						else
						{
							Console.Write("-"); // Line on top and bottom (original symbol: u2501)
						}
					}
					else
					{
						// Make a border side draw
						if (x == 0 || x == maxWidth - 1)
						{
							Console.Write("|"); // Right and left column (original symbol: u2503)
						}
					}
				}
			}

			if (setCursorPosX != null)
			{
				if (setCursorPosX >= 0 && setCursorPosX < maxWidth)
				{
					actualCursorPosX = (int)setCursorPosX;
				}
			}

			if (setCursorPosY != null)
			{
				if (setCursorPosY >= 0 && setCursorPosY < maxHeight)
				{
					actualCursosPosY = (int)setCursorPosY;
				}
			}

			Console.SetCursorPosition(actualCursorPosX, actualCursosPosY);
		}
	}
}
