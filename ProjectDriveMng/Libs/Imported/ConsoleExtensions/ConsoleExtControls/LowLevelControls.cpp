#include "LowLevelControls.hpp"

void ConsoleExt::LowLevel::Bell()
{
	std::string s = CONSOLE_EXT_BELL;
	std::cout << s;
}

void ConsoleExt::LowLevel::BellW()
{
	std::wstring s = CONSOLE_EXT_BELL_W;
	std::wcout << s;
}

void ConsoleExt::LowLevel::Backspace()
{
    std::string s = CONSOLE_EXT_BACKSPACE;
	std::cout << s;
}

void ConsoleExt::LowLevel::BackspaceW()
{
	std::wstring s = CONSOLE_EXT_BACKSPACE_W;
	std::wcout << s;
}

void ConsoleExt::LowLevel::HorizontalTab()
{
	std::string s = CONSOLE_EXT_HORIZONTAL_TAB;
	std::cout << s;
}

void ConsoleExt::LowLevel::HorizontalTabW()
{
	std::wstring s = CONSOLE_EXT_HORIZONTAL_TAB_W;
	std::wcout << s;
}

void ConsoleExt::LowLevel::VerticalTab()
{
    std::string s = CONSOLE_EXT_VERTICAL_TAB;
	std::cout << s;
}

void ConsoleExt::LowLevel::VerticalTabW()
{
	std::wstring s = CONSOLE_EXT_VERTICAL_TAB_W;
	std::wcout << s;
}

void ConsoleExt::LowLevel::FormFeed()
{
    std::string s = CONSOLE_EXT_FORM_FEED;
	std::cout << s;
}

void ConsoleExt::LowLevel::FormFeedW()
{
	std::wstring s = CONSOLE_EXT_FORM_FEED_W;
	std::wcout << s;
}

void ConsoleExt::LowLevel::SaveCursorPosition()
{
	std::string s = CONSOLE_EXT_SAVE_CURSOR_POS;
	std::cout << s;
}

void ConsoleExt::LowLevel::SaveCursorPositionW()
{
	std::wstring s = CONSOLE_EXT_SAVE_CURSOR_POS_W;
	std::wcout << s;
}

void ConsoleExt::LowLevel::RestoreCursorPosition()
{
	std::string s = CONSOLE_EXT_RESTORE_CURSOR_POS;
	std::cout << s;
}

void ConsoleExt::LowLevel::RestoreCursorPositionW()
{
    std::wstring s = CONSOLE_EXT_RESTORE_CURSOR_POS_W;
	std::wcout << s;
}

void ConsoleExt::LowLevel::MoveCursorUp(int y)
{
    std::string s = CONSOLE_EXT_CURSOR_UP(y);
	std::cout << s;
}

void ConsoleExt::LowLevel::MoveCursorUpW(int y)
{
    std::wstring s = CONSOLE_EXT_CURSOR_UP_W(y);
	std::wcout << s;
}

void ConsoleExt::LowLevel::MoveCursorDown(int y)
{
    std::string s = CONSOLE_EXT_CURSOR_DOWN(y);
	std::cout << s;
}

void ConsoleExt::LowLevel::MoveCursorDownW(int y)
{
    std::wstring s = CONSOLE_EXT_CURSOR_DOWN_W(y);
	std::wcout << s;
}

void ConsoleExt::LowLevel::MoveCursorForward(int x)
{
    std::string s = CONSOLE_EXT_CURSOR_FORWARD(x);
	std::cout << s;
}

void ConsoleExt::LowLevel::MoveCursorForwardW(int x)
{
    std::wstring s = CONSOLE_EXT_CURSOR_FORWARD_W(x);
	std::wcout << s;
}

void ConsoleExt::LowLevel::MoveCursorBack(int x)
{
    std::string s = CONSOLE_EXT_CURSOR_BACK(x);
	std::cout << s;
}

void ConsoleExt::LowLevel::MoveCursorBackW(int x)
{
	std::wstring s = CONSOLE_EXT_CURSOR_BACK_W(x);
	std::wcout << s;
}

void ConsoleExt::LowLevel::NextLine(int n)
{
    std::string s = CONSOLE_EXT_CURSOR_NEXT_LINE(n);
	std::cout << s;
}

void ConsoleExt::LowLevel::NextLineW(int n)
{
	std::wstring s = CONSOLE_EXT_CURSOR_NEXT_LINE_W(n);
	std::wcout << s;
}

void ConsoleExt::LowLevel::PreviousLine(int n)
{
	std::string s = CONSOLE_EXT_CURSOR_PREVIOUS_LINE(n);
	std::cout << s;
}

void ConsoleExt::LowLevel::PreviousLineW(int n)
{
	std::wstring s = CONSOLE_EXT_CURSOR_PREVIOUS_LINE_W(n);
	std::wcout << s;
}

void ConsoleExt::LowLevel::HorizontalAbsolute(int n)
{
	std::string s = CONSOLE_EXT_CURSOR_HORIZONTAL_ABSOLUTE(n);
	std::cout << s;
}

void ConsoleExt::LowLevel::HorizontalAbsoluteW(int n)
{
	std::wstring s = CONSOLE_EXT_CURSOR_HORIZONTAL_ABSOLUTE_W(n);
	std::wcout << s;
}

void ConsoleExt::LowLevel::SetCursorPosition(int x, int y)
{
	std::string s = CONSOLE_EXT_CURSOR_POS(x, y);
	std::cout << s;
}

void ConsoleExt::LowLevel::SetCursorPositionW(int x, int y)
{
	std::wstring s = CONSOLE_EXT_CURSOR_POS_W(x, y);
	std::wcout << s;
}

void ConsoleExt::LowLevel::EraseDisplay(int t)
{
	std::string s = CONSOLE_EXT_ERASE_DISPLAY(t);
	std::cout << s;
}

void ConsoleExt::LowLevel::EraseDisplayW(int t)
{
    std::wstring s = CONSOLE_EXT_ERASE_DISPLAY_W(t);
	std::wcout << s;
}

void ConsoleExt::LowLevel::EraseLine(int t)
{
	std::string s = CONSOLE_EXT_ERASE_LINE(t);
	std::cout << s;
}

void ConsoleExt::LowLevel::EraseLineW(int t)
{
	std::wstring s = CONSOLE_EXT_ERASE_LINE_W(t);
	std::wcout << s;
}

void ConsoleExt::LowLevel::ScrollUp(int n)
{
    std::string s = CONSOLE_EXT_SCROLL_UP(n);
	std::cout << s;
}

void ConsoleExt::LowLevel::ScrollUpW(int n)
{
	std::wstring s = CONSOLE_EXT_SCROLL_UP_W(n);
	std::wcout << s;
}

void ConsoleExt::LowLevel::ScrollDown(int n)
{
	std::string s = CONSOLE_EXT_SCROLL_DOWN(n);
	std::cout << s;
}

void ConsoleExt::LowLevel::ScrollDownW(int n)
{
	std::wstring s = CONSOLE_EXT_SCROLL_DOWN_W(n);
	std::wcout << s;
}
