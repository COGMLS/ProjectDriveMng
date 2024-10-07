#pragma once

#ifndef CONSOLE_EXT_GRAPHIC_INTERFACE_HPP
#define CONSOLE_EXT_GRAPHIC_INTERFACE_HPP

#ifdef WIN32
	#ifdef CONSOLE_EXT_GRAPHIC_INTERFACE_EXPORTS
		#define CONSOLE_EXT_GRAPHIC_INTERFACE_LIB_API __declspec(dllexport)
	#else
		#define CONSOLE_EXT_GRAPHIC_INTERFACE_LIB_API __declspec(dllimport)
	#endif //!CONSOLE_EXT_GRAPHIC_INTERFACE_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)

	//Remove warning C4566
	#pragma warning (disable : 4566)
#else
	#if __GNUC__ >= 4
		#ifdef CONSOLE_EXT_GRAPHIC_INTERFACE_EXPORTS
			#define CONSOLE_EXT_GRAPHIC_INTERFACE_LIB_API __attribute__((visibility("default")))
		#else
			#define CONSOLE_EXT_GRAPHIC_INTERFACE_LIB_API __attribute__((visibility("default")))
		#endif //!CONSOLE_EXT_GRAPHIC_INTERFACE_EXPORTS
	#else
		#ifdef CONSOLE_EXT_GRAPHIC_INTERFACE_EXPORTS
			#define CONSOLE_EXT_GRAPHIC_INTERFACE_LIB_API
		#else
			#define CONSOLE_EXT_GRAPHIC_INTERFACE_LIB_API
		#endif //!CONSOLE_EXT_GRAPHIC_INTERFACE_EXPORTS
	#endif
#endif // !WIN32

#include <iostream>
#include <string>

// Import the ConsoleExtControls:
#include "ConsoleControls.hpp"

// Internal library headers:
#include "ConsoleExtException.hpp"
#include "AsciiGraphicInterface.hpp"

namespace ConsoleExt
{
	/**
	 * @brief Draw a border in the console screen
	 * @param startPosX Define the start position on X-axis
	 * @param startPosY Define the start position on Y-axis
	 * @param maxWidth Define the end of the border on X-axis
	 * @param maxHeight Define the end of the border on Y-axis
	 * @param CONSOLE_EXT_SET_CURSOR_POSX Define the cursor position after draw the border position on X-axis
	 * @param CONSOLE_EXT_SET_CURSOR_POSY Define the cursor position after draw the border position on Y-axis
	 * @note startPosX and startPosY need be greater than zero.
	 * @note If CONSOLE_EXT_SET_CURSOR_POSX or CONSOLE_EXT_SET_CURSOR_POSY holds zero or a negative value, the cursor will be restored to last position before draw the border.
	 */
	CONSOLE_EXT_GRAPHIC_INTERFACE_LIB_API void DrawBorder(int startPosX, int startPosY, int maxWidth, int maxHeight, int CONSOLE_EXT_SET_CURSOR_POSX, int CONSOLE_EXT_SET_CURSOR_POSY);

	/**
	 * @brief Draw a border in the console screen
	 * @param startPosX Define the start position on X-axis
	 * @param startPosY Define the start position on Y-axis
	 * @param maxWidth Define the end of the border on X-axis
	 * @param maxHeight Define the end of the border on Y-axis
	 * @param CONSOLE_EXT_SET_CURSOR_POSX Define the cursor position after draw the border position on X-axis
	 * @param CONSOLE_EXT_SET_CURSOR_POSY Define the cursor position after draw the border position on Y-axis
	 * @note startPosX and startPosY need be greater than zero.
	 * @note If CONSOLE_EXT_SET_CURSOR_POSX or CONSOLE_EXT_SET_CURSOR_POSY holds zero or a negative value, the cursor will be restored to last position before draw the border.
	 */
	CONSOLE_EXT_GRAPHIC_INTERFACE_LIB_API void DrawBorderW(int startPosX, int startPosY, int maxWidth, int maxHeight, int CONSOLE_EXT_SET_CURSOR_POSX, int CONSOLE_EXT_SET_CURSOR_POSY);

	/**
	 * @brief Draw a horizontal line in the console screen
	 * @param xStart Start position on X-axis
	 * @param yStart Start position on Y-axis
	 * @param count How many chars on console screen will be used to the line
	 * @param useStartCrossLine Use a cross line mark
	 * @param useEndCrossLine Use a end cross line mark
	 */
	CONSOLE_EXT_GRAPHIC_INTERFACE_LIB_API void DrawHorizontalLine(int xStart, int yStart, int count, bool useStartCrossLine, bool useEndCrossLine);

	/**
	 * @brief Draw a horizontal line in the console screen
	 * @param xStart Start position on X-axis
	 * @param yStart Start position on Y-axis
	 * @param count How many chars on console screen will be used to the line
	 * @param useStartCrossLine Use a cross line mark
	 * @param useEndCrossLine Use a end cross line mark
	 */
	CONSOLE_EXT_GRAPHIC_INTERFACE_LIB_API void DrawHorizontalLineW(int xStart, int yStart, int count, bool useStartCrossLine, bool useEndCrossLine);

	/**
	 * @brief Draw a progress bar with a counter and the final value to be reached
	 * @param progressBarXPos Define the progress bar position on X-axis
	 * @param progressBarYPor Define the progress bar position on Y-axis
	 * @param maxWidth Define the maximum characters will be used to progress bar and counter informations
	 * @param maxValue Final value that need be reached
	 * @param actualValue Actual value in progress bar. NOTE: The progress bar need be called again to update the console informations
	 */
	CONSOLE_EXT_GRAPHIC_INTERFACE_LIB_API void DrawProgressBar(int progressBarXPos, int progressBarYPor, int maxWidth, int maxValue, int actualValue);

	/**
	 * @brief Draw a progress bar with a counter and the final value to be reached
	 * @param progressBarXPos Define the progress bar position on X-axis
	 * @param progressBarYPor Define the progress bar position on Y-axis
	 * @param maxWidth Define the maximum characters will be used to progress bar and counter informations
	 * @param maxValue Final value that need be reached
	 * @param actualValue Actual value in progress bar. NOTE: The progress bar need be called again to update the console informations
	 */
	CONSOLE_EXT_GRAPHIC_INTERFACE_LIB_API void DrawProgressBarW(int progressBarXPos, int progressBarYPor, int maxWidth, int maxValue, int actualValue);
}

#endif //!CONSOLE_EXT_GRAPHIC_INTERFACE_HPP