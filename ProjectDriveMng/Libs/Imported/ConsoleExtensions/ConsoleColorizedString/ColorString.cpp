#include "ColorString.hpp"

std::string ConsoleExt::ColorizeString(std::string str, ConsoleExt::ConsoleForegroundColor fColor)
{
	std::string temp = "";
	temp = "\033[" + std::to_string(fColor) + 'm';
	temp += str;
	temp += "\033[0m";

	return temp;
}

std::string ConsoleExt::ColorizeString(std::string str, ConsoleExt::ConsoleBackgroundColor bColor)
{
	std::string temp = "";
	temp = "\033[" + std::to_string(bColor) + 'm';
	temp += str;
	temp += "\033[0m";

	return temp;
}

std::string ConsoleExt::ColorizeString(std::string str, ConsoleExt::ConsoleForegroundColor fColor, ConsoleExt::ConsoleBackgroundColor bColor)
{
	std::string temp = "";
	temp = "\033[" + std::to_string(bColor) + ';' + std::to_string(fColor) + 'm';
	temp += str;
	temp += "\033[0m";

	return temp;
}

std::string ConsoleExt::ColorizeString(std::string str, unsigned int color, bool background)
{
	std::string temp = "";

	int r = color & 0xFF0000;
	int g = color & 0x00FF00;
	int b = color & 0x0000FF;

	r = r >> 16;
	g = g >> 8;

	if (background)
	{
		temp = CSI + std::to_string(SgrOptions::CustomBackgroundColor) + ";";
	}
	else
	{
		temp = CSI + std::to_string(SgrOptions::CustomForegroundColor) + ";";
	}

	temp += "2;";
	temp += std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";

	temp += str;

	if (background)
	{
		temp += CSI + std::to_string(SgrOptions::DefaultBackgroundColor) + "m";
	}
	else
	{
		temp += CSI + std::to_string(SgrOptions::DefaultForegroundColor) + "m";
	}

	return temp;
}

std::string ConsoleExt::ColorizeString(std::string str, ConsoleExt::ColorData color, bool background)
{
    std::string temp = "";

	int r = static_cast<int>(color.r);
	int g = static_cast<int>(color.g);
	int b = static_cast<int>(color.b);

	if (background)
	{
		temp = CSI + std::to_string(SgrOptions::CustomBackgroundColor) + ";";
	}
	else
	{
		temp = CSI + std::to_string(SgrOptions::CustomForegroundColor) + ";";
	}

	temp += "2;";
	temp += std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";

	temp += str;

	if (background)
	{
		temp += CSI + std::to_string(SgrOptions::DefaultBackgroundColor) + "m";
	}
	else
	{
		temp += CSI + std::to_string(SgrOptions::DefaultForegroundColor) + "m";
	}

	return temp;
}

std::string ConsoleExt::ColorizeString(std::string str, unsigned int fColor, unsigned int bColor)
{
    std::string temp = "";

	int r = fColor & 0xFF0000;
	int g = fColor & 0x00FF00;
	int b = fColor & 0x0000FF;

	r = r >> 16;
	g = g >> 8;

	temp = CSI + std::to_string(SgrOptions::CustomForegroundColor) + ";2;";
	temp += std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";

	r = bColor & 0xFF0000;
	g = bColor & 0x00FF00;
	b = bColor & 0x0000FF;

	r = r >> 16;
	g = g >> 8;

	temp += CSI + std::to_string(SgrOptions::CustomBackgroundColor) + ";2;";
	temp += std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";

	temp += str;

	temp += CSI + std::to_string(SgrOptions::DefaultForegroundColor) + "m";
	temp += CSI + std::to_string(SgrOptions::DefaultBackgroundColor) + "m";

	//temp += CSI + std::to_string(SgrOptions::ResetConsole) + "m";

	return temp;
}

std::string ConsoleExt::ColorizeString(std::string str, ConsoleExt::ColorData fColor, ConsoleExt::ColorData bColor)
{
	std::string temp = "";

	int r = static_cast<int>(fColor.r);
	int g = static_cast<int>(fColor.g);
	int b = static_cast<int>(fColor.b);

	temp = CSI + std::to_string(SgrOptions::CustomForegroundColor) + ";2;";
	temp += std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";

	r = static_cast<int>(bColor.r);
	g = static_cast<int>(bColor.g);
	b = static_cast<int>(bColor.b);

	temp += CSI + std::to_string(SgrOptions::CustomBackgroundColor) + ";2;";
	temp += std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";

	temp += str;

	temp += CSI + std::to_string(SgrOptions::DefaultForegroundColor) + "m";
	temp += CSI + std::to_string(SgrOptions::DefaultBackgroundColor) + "m";

	//temp += CSI + std::to_string(SgrOptions::ResetConsole) + "m";

	return temp;
}

std::string ConsoleExt::UnColorizeString(std::string str)
{
	std::string temp = "";

	bool foundedInitMark = false;
	bool foundedInitMarkEnd = false;
	bool foundedFinalMark = false;
	bool foundedFinalMarkEnd = false;
	
	int IndexStart = 0;
	int IndexEnd = 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (!foundedInitMark && !foundedFinalMarkEnd && !foundedFinalMark && !foundedFinalMarkEnd)
		{
			if (str[i] == '\033')
			{
				foundedInitMark = true;
			}
		}

		if (foundedInitMark && !foundedInitMarkEnd)
		{
			if (str[i] == 'm')
			{
				foundedInitMarkEnd = true;
				IndexStart = i + 1;
			}
		}

		if (foundedInitMark && foundedInitMarkEnd && !foundedFinalMark && !foundedFinalMarkEnd)
		{
			if (str[i] == '\033')
			{
				foundedFinalMark = true;
				IndexEnd = i - 1;
			}
		}

		if (foundedFinalMark && !foundedFinalMarkEnd)
		{
			if (str[i] == 'm')
			{
				foundedFinalMarkEnd = true;
			}
		}
	}

	if (foundedInitMark && foundedInitMarkEnd && foundedFinalMark && foundedFinalMarkEnd && (IndexEnd < str.size()))
	{
		for (int i = IndexStart; i <= IndexEnd; i++)
		{
			temp += str[i];
		}

		return temp;
	}
	else
	{
		//return "Fail" + std::to_string(IndexStart) + ';' + std::to_string(IndexEnd);
		return str;
	}
}