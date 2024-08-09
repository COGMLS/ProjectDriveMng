using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DotNetConsoleExtensions
{
	internal static class MenuMng
	{
		private static List<Menu> menus = new List<Menu>();
		private static int ids = 0;

		/// <summary>
		/// Get a menu object to manipulate
		/// </summary>
		/// <param name="id"></param>
		/// <returns>
		/// Return the menu searched by ID.
		/// Return a "NULL_MENU" when no menu was registered or found.
		/// </returns>
		public static Menu GetMenu(int id)
		{
			if (menus.Count == 0)
			{
				return new Menu();
			}

			for (int i = 0; i < menus.Count; i++)
			{
				if (menus[i].Id == id)
				{
					return menus[i];
				}
			}

			return new Menu();
		}

		/// <summary>
		/// Update the menu list
		/// </summary>
		/// <param name="menu"></param>
		/// <returns>
		/// 0 : Menu added because no menu was registered
		/// 1 : Menu found and updated
		/// 2 : Menu not found and added in register
		/// </returns>
		public static int UpdateMenu(Menu menu)
		{
			if (menus.Count == 0)
			{
				menus.Add(menu);
				return 0;
			}

			for (int i = 0; i < menus.Count; i++)
			{
				if (menu.Id == menus[i].Id)
				{
					menus[i] = menu;
					return 1;
				}
			}

			menus.Add(menu);
			return 2;
		}
	}
}
