#pragma once

#ifndef CONSOLE_EXT_LOW_LEVEL_CONTROLS_HPP
#define CONSOLE_EXT_LOW_LEVEL_CONTROLS_HPP

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

#include <iostream>
#include <string>

#include "AsciiControls.hpp"

#include "ConsoleExtException.hpp"

namespace ConsoleExt
{
	namespace LowLevel
	{

		/**
		 * @brief Makes an audible noise
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void Bell();

		/**
		 * @brief Makes an audible noise
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void BellW();

		/**
		 * @brief Moves the cursor left (but may "backwards wrap" if cursor is at start of line).
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void Backspace();

		/**
		 * @brief Moves the cursor left (but may "backwards wrap" if cursor is at start of line).
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void BackspaceW();

		/**
		 * @brief Move the cursor position right to the next tab stop.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void HorizontalTab();

		/**
		 * @brief Move the cursor position right to the next tab stop.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void HorizontalTabW();

		/**
		 * @brief Vertical tabulation
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void VerticalTab();

		/**
		 * @brief Vertical tabulation
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void VerticalTabW();

		/**
		 * @brief Move the cursor to top of next page. Usually does not move horizontally, though programs should not rely on this.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void FormFeed();

		/**
		 * @brief Move the cursor to top of next page. Usually does not move horizontally, though programs should not rely on this.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void FormFeedW();

		/**
		 * @brief Save the current cursor's position
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void SaveCursorPosition();

		/**
		 * @brief Save the current cursor's position
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void SaveCursorPositionW();

		/**
		 * @brief Restore the cursor position saved by the SaveCursorPosition method
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void RestoreCursorPosition();

		/**
		 * @brief Restore the cursor position saved by the SaveCursorPositionW method
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void RestoreCursorPositionW();

		/**
		 * @brief Moves the cursor n (default 1) cells in the given direction. If the cursor is already at the edge of the screen, this has no effect.
		 * @param y Number of positions that will be shifted vertically
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void MoveCursorUp(int y);

		/**
		 * @brief Moves the cursor n (default 1) cells in the given direction. If the cursor is already at the edge of the screen, this has no effect.
		 * @param y Number of positions that will be shifted vertically
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void MoveCursorUpW(int y);

		/**
		 * @brief Moves the cursor n (default 1) cells in the given direction. If the cursor is already at the edge of the screen, this has no effect.
		 * @param y Number of positions that will be shifted vertically
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void MoveCursorDown(int y);

		/**
		 * @brief Moves the cursor n (default 1) cells in the given direction. If the cursor is already at the edge of the screen, this has no effect.
		 * @param y Number of positions that will be shifted vertically
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void MoveCursorDownW(int y);

		/**
		 * @brief Moves the cursor n (default 1) cells in the given direction. If the cursor is already at the edge of the screen, this has no effect.
		 * @param y Number of positions that will be shifted horizontally
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void MoveCursorForward(int x);

		/**
		 * @brief Moves the cursor n (default 1) cells in the given direction. If the cursor is already at the edge of the screen, this has no effect.
		 * @param y Number of positions that will be shifted horizontally
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void MoveCursorForwardW(int x);

		/**
		 * @brief Moves the cursor n (default 1) cells in the given direction. If the cursor is already at the edge of the screen, this has no effect.
		 * @param y Number of positions that will be shifted horizontally
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void MoveCursorBack(int x);

		/**
		 * @brief Moves the cursor n (default 1) cells in the given direction. If the cursor is already at the edge of the screen, this has no effect.
		 * @param y Number of positions that will be shifted horizontally
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void MoveCursorBackW(int x);

		/**
		 * @brief Moves cursor to beginning of the line n (default 1) lines down.
		 * @param n Number of lines to be shifted.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void NextLine(int n);

		/**
		 * @brief Moves cursor to beginning of the line n (default 1) lines down.
		 * @param n Number of lines to be shifted.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void NextLineW(int n);

		/**
		 * @brief Moves cursor to beginning of the line n (default 1) lines up.
		 * @param n Number of lines to be shifted.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void PreviousLine(int n);

		/**
		 * @brief Moves cursor to beginning of the line n (default 1) lines up.
		 * @param n Number of lines to be shifted.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void PreviousLineW(int n);

		/**
		 * @brief Moves the cursor to column n (default 1).
		 * @param n Columns to be shifted.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void HorizontalAbsolute(int n);

		/**
		 * @brief Moves the cursor to column n (default 1).
		 * @param n Columns to be shifted.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void HorizontalAbsoluteW(int n);
		
		/**
		 * @brief Set the console cursor's position
		 * @param x Position on X-axis (default 1)
		 * @param y Position on Y-axis (default 1)
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void SetCursorPosition(int x, int y);
		
		/**
		 * @brief Set the console cursor's position
		 * @param x Position on X-axis (default 1)
		 * @param y Position on Y-axis (default 1)
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void SetCursorPositionW(int x, int y);

		/**
		 * @brief Erase the display screen
		 * @param t If t is 0, clear from cursor screen. If t is 1, clear from cursor to begging of the screen. If t is 2, clear entire screen and moves the cursor on upper left (depending the console). If t is 3, clear the entire screen and delete all lines saved in the scrollback buffer.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void EraseDisplay(int t);

		/**
		 * @brief Erase the display screen
		 * @param t If t is 0, clear from cursor screen. If t is 1, clear from cursor to begging of the screen. If t is 2, clear entire screen and moves the cursor on upper left (depending the console). If t is 3, clear the entire screen and delete all lines saved in the scrollback buffer.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void EraseDisplayW(int t);

		/**
		 * @brief Erase the line on screen buffer. The cursor position does not change.
		 * @param t If t is 0, clear from cursor to the end of the line. If t is 1, clear from cursor to begging of the line. If t is 2, clear entire line. The cursor"s position does not change.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void EraseLine(int t);

		/**
		 * @brief Erase the line on screen buffer. The cursor position does not change.
		 * @param t If t is 0, clear from cursor to the end of the line. If t is 1, clear from cursor to begging of the line. If t is 2, clear entire line. The cursor"s position does not change.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void EraseLineW(int t);

		/**
		 * @brief Scroll whole page up by n (default 1) lines. New lines are added at the bottom.
		 * @param n Number of lines that will be scrolled.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void ScrollUp(int n);

		/**
		 * @brief Scroll whole page up by n (default 1) lines. New lines are added at the bottom.
		 * @param n Number of lines that will be scrolled.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void ScrollUpW(int n);

		/**
		 * @brief Scroll whole page down by n (default 1) lines. New lines are added at the top.
		 * @param n Number of lines that will be scrolled.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void ScrollDown(int n);

		/**
		 * @brief Scroll whole page down by n (default 1) lines. New lines are added at the top.
		 * @param n Number of lines that will be scrolled.
		 */
		CONSOLE_EXT_CONSOLE_CONTROLS_LIB_API void ScrollDownW(int n);
	}
}

#endif // !CONSOLE_EXT_LOW_LEVEL_CONTROLS_HPP