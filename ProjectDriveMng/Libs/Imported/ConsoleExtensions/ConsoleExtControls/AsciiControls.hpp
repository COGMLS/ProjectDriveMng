#pragma once

#ifndef CONSOLE_EXT_ASCII_CONTROLS_HPP
#define CONSOLE_EXT_ASCII_CONTROLS_HPP

#ifdef WIN32
	#ifdef CONSOLE_EXT_CONSOLE_CONTROLS_EXPORTS
		#define CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API __declspec(dllexport)
	#else
		#define CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API __declspec(dllimport)
	#endif //!CONSOLE_EXT_CONSOLE_CONTROLS_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef CONSOLE_EXT_CONSOLE_CONTROLS_EXPORTS
			#define CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API __attribute__((visibility("default")))
		#else
			#define CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API __attribute__((visibility("default")))
		#endif //!CONSOLE_EXT_CONSOLE_CONTROLS_EXPORTS
	#else
		#ifdef CONSOLE_EXT_CONSOLE_CONTROLS_EXPORTS
			#define CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API
		#else
			#define CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API
		#endif //!CONSOLE_EXT_CONSOLE_CONTROLS_EXPORTS
	#endif
#endif // !WIN32

#include <string>

//
// ASCII Controls:
//

//
// ASCII Basic Controls:
//

#define ESC 		"\x1B"								// Escape control
#define ESC_W 		L"\x1B"								// Escape control

#define CSI 		ESC "["								// Control Sequence Introducer
#define CSI_W 		ESC_W L"["							// Control Sequence Introducer

#define SGR(n) 		CSI + std::to_string(n) + "m"		// Select Graphic Rendition
#define SGR_W(n) 	CSI_W + std::to_wstring(n) + L"m"	// Select Graphic Rendition

//
// Console Basic Controls:
//

#define CONSOLE_EXT_BELL 				"\x07"
#define CONSOLE_EXT_BELL_W 				L"\x07"

#define CONSOLE_EXT_BACKSPACE 			"\x08"
#define CONSOLE_EXT_BACKSPACE_W 		L"\x08"

#define CONSOLE_EXT_HORIZONTAL_TAB 		"\x09"
#define CONSOLE_EXT_HORIZONTAL_TAB_W 	L"\x09"

#define CONSOLE_EXT_VERTICAL_TAB 		"\x0b"
#define CONSOLE_EXT_VERTICAL_TAB_W 		L"\x0b"

#define CONSOLE_EXT_FORM_FEED 			"\x0c"
#define CONSOLE_EXT_FORM_FEED_W 		L"\x0c"

//
// Cursor Controls:
//

#define CONSOLE_EXT_SAVE_CURSOR_POS 				ESC" 7"
#define CONSOLE_EXT_RESTORE_CURSOR_POS 				ESC" 8"

#define CONSOLE_EXT_CURSOR_UP(y) 					CSI + std::to_string(y) + "A"
#define CONSOLE_EXT_CURSOR_DOWN(y) 					CSI + std::to_string(y) + "B"
#define CONSOLE_EXT_CURSOR_FORWARD(x) 				CSI + std::to_string(x) + "C"
#define CONSOLE_EXT_CURSOR_BACK(x) 					CSI + std::to_string(x) + "D"
#define CONSOLE_EXT_CURSOR_NEXT_LINE(n) 			CSI + std::to_string(n) + "E"
#define CONSOLE_EXT_CURSOR_PREVIOUS_LINE(n) 		CSI + std::to_string(n) + "F"
#define CONSOLE_EXT_CURSOR_HORIZONTAL_ABSOLUTE(n) 	CSI + std::to_string(n) + "G"
#define CONSOLE_EXT_CURSOR_POS(x,y) 				CSI + std::to_string(y) + ";" + std::to_string(x) + "H"

// Wide chars Controls:

#define CONSOLE_EXT_SAVE_CURSOR_POS_W 				ESC_W L" 7"
#define CONSOLE_EXT_RESTORE_CURSOR_POS_W 			ESC_W L" 8"

#define CONSOLE_EXT_CURSOR_UP_W(y) 					CSI_W + std::to_wstring(y) + L"A"
#define CONSOLE_EXT_CURSOR_DOWN_W(y) 				CSI_W + std::to_wstring(y) + L"B"
#define CONSOLE_EXT_CURSOR_FORWARD_W(x) 			CSI_W + std::to_wstring(x) + L"C"
#define CONSOLE_EXT_CURSOR_BACK_W(x) 				CSI_W + std::to_wstring(x) + L"D"
#define CONSOLE_EXT_CURSOR_NEXT_LINE_W(n) 			CSI_W + std::to_wstring(n) + L"E"
#define CONSOLE_EXT_CURSOR_PREVIOUS_LINE_W(n) 		CSI_W + std::to_wstring(n) + L"F"
#define CONSOLE_EXT_CURSOR_HORIZONTAL_ABSOLUTE_W(n)	CSI_W + std::to_wstring(n) + L"G"
#define CONSOLE_EXT_CURSOR_POS_W(x,y) 				CSI_W + std::to_wstring(y) + L";" + std::to_wstring(x) + L"H"

//
// Buffer Controls:
//

// Erase the Display: If t is 0, clear from cursor screen. If t is 1, clear from cursor to begging of the screen. If t is 2, clear entire screen and moves the cursor on upper left (depending the console). If t is 3, clear the entire screen and delete all lines saved in the scrollback buffer.
#define CONSOLE_EXT_ERASE_DISPLAY(t) 	CSI + std::to_string(t) + "J"

// Erase the line: If t is 0, clear from cursor to the end of the line. If t is 1, clear from cursor to begging of the line. If t is 2, clear entire line. The cursor"s position does not change.
#define CONSOLE_EXT_ERASE_LINE(t) 		CSI + std::to_string(t) + "K"

#define CONSOLE_EXT_SCROLL_UP(n) 		CSI + std::to_string(n) + "S"

#define CONSOLE_EXT_SCROLL_DOWN(n) 		CSI + std::to_string(n) + "T"

// Wide chars controls:

// Erase the Display: If t is 0, clear from cursor screen. If t is 1, clear from cursor to begging of the screen. If t is 2, clear entire screen and moves the cursor on upper left (depending the console). If t is 3, clear the entire screen and delete all lines saved in the scrollback buffer.
#define CONSOLE_EXT_ERASE_DISPLAY_W(t) 	CSI_W + std::to_wstring(t) + L"J"

// Erase the line: If t is 0, clear from cursor to the end of the line. If t is 1, clear from cursor to begging of the line. If t is 2, clear entire line. The cursor"s position does not change.
#define CONSOLE_EXT_ERASE_LINE_W(t) 	CSI_W + std::to_wstring(t) + L"K"

#define CONSOLE_EXT_SCROLL_UP_W(n) 		CSI_W + std::to_wstring(n) + L"S"

#define CONSOLE_EXT_SCROLL_DOWN_W(n) 	CSI_W + std::to_wstring(n) + L"T"

#endif // !CONSOLE_EXT_ASCII_CONTROLS_HPP