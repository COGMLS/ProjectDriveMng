#include "ColorWstring.hpp"

std::wstring ConsoleExt::ColorizeWstring(std::wstring wstr, ConsoleExt::ConsoleForegroundColor fColor)
{
	std::wstring temp = L"";
	temp = L"\033[" + std::to_wstring(fColor) + L'm';
	temp += wstr;
	temp += L"\033[0m";

	return temp;
}

std::wstring ConsoleExt::ColorizeWstring(std::wstring wstr, ConsoleExt::ConsoleBackgroundColor bColor)
{
	std::wstring temp = L"";
	temp = L"\033[" + std::to_wstring(bColor) + L'm';
	temp += wstr;
	temp += L"\033[0m";

	return temp;
}

std::wstring ConsoleExt::ColorizeWstring(std::wstring wstr, ConsoleExt::ConsoleForegroundColor fColor, ConsoleExt::ConsoleBackgroundColor bColor)
{
	std::wstring temp = L"";
	temp = L"\033[" + std::to_wstring(bColor) + L';' + std::to_wstring(fColor) + L'm';
	temp += wstr;
	temp += L"\033[0m";

	return temp;
}

std::wstring ConsoleExt::UnColorizeWstring(std::wstring wstr)
{
	std::wstring temp = L"";

	bool foundedInitMark = false;
	bool foundedInitMarkEnd = false;
	bool foundedFinalMark = false;
	bool foundedFinalMarkEnd = false;

	int IndexStart = 0;
	int IndexEnd = 0;

	for (int i = 0; i < wstr.size(); i++)
	{
		if (!foundedInitMark && !foundedFinalMarkEnd && !foundedFinalMark && !foundedFinalMarkEnd)
		{
			if (wstr[i] == L'\033')
			{
				foundedInitMark = true;
			}
		}

		if (foundedInitMark && !foundedInitMarkEnd)
		{
			if (wstr[i] == L'm')
			{
				foundedInitMarkEnd = true;
				IndexStart = i + 1;
			}
		}

		if (foundedInitMark && foundedInitMarkEnd && !foundedFinalMark && !foundedFinalMarkEnd)
		{
			if (wstr[i] == L'\033')
			{
				foundedFinalMark = true;
				IndexEnd = i - 1;
			}
		}

		if (foundedFinalMark && !foundedFinalMarkEnd)
		{
			if (wstr[i] == L'm')
			{
				foundedFinalMarkEnd = true;
			}
		}
	}

	if (foundedInitMark && foundedInitMarkEnd && foundedFinalMark && foundedFinalMarkEnd && (IndexEnd < wstr.size()))
	{
		for (int i = IndexStart; i <= IndexEnd; i++)
		{
			temp += wstr[i];
		}

		return temp;
	}
	else
	{
		//return L"Fail" + std::to_wstring(IndexStart) + L';' + std::to_wstring(IndexEnd);
		return wstr;
	}
}