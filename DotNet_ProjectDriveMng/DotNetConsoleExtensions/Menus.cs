using System;

namespace DotNetConsoleExtensions
{
	public class Menu
	{
		// -1 means a NULL_MENU
		public readonly int Id;
		private string name;
		private string? description;
		private MenuMessage[]? messages;
		private int style;

		public Menu()
		{
			this.Id = -1;
			this.name = "NULL_MENU";
			this.description = null;
			this.messages = null;
		}

		public Menu (string name, string? description, MenuMessage[]? messages)
		{
			this.name = name;
			this.description = description;
			this.messages = messages;
		}

		public void UpdateMenuData (string name, string? description)
		{
			this.name = name;
			this.description = description;
		}

		public void UpdateMenuData(MenuMessage[] messages)
		{
			this.messages = messages;
		}

		public void Draw(bool drawBorders = false, int? setCursorPosX = null, int? setCursorPosY = null)
		{
			int maxHeight = Console.BufferHeight;
			int maxWidth = Console.BufferWidth;

			int actualCursorPosX = Console.GetCursorPosition().Top;
			int actualCursosPosY = Console.GetCursorPosition().Left;

			if (drawBorders)
			{
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
			}
		}
	}
}
