#pragma once

#ifndef COLOR_WSTRING_HPP
#define COLOR_WSTRING_HPP

#ifdef WIN32
	#ifdef CONSOLE_EXT_COLOR_STR_EXPORTS
		#define CONSOLE_EXT_COLOR_STR_LIB_API __declspec(dllexport)
	#else
		#define CONSOLE_EXT_COLOR_STR_LIB_API __declspec(dllimport)
	#endif //!CONSOLE_EXT_COLOR_STR_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef CONSOLE_EXT_COLOR_STR_EXPORTS
			#define CONSOLE_EXT_COLOR_STR_LIB_API __attribute__((visibility("default")))
		#else
			#define CONSOLE_EXT_COLOR_STR_LIB_API __attribute__((visibility("default")))
		#endif //!CONSOLE_EXT_COLOR_STR_EXPORTS
	#else
		#ifdef CONSOLE_EXT_COLOR_STR_EXPORTS
			#define CONSOLE_EXT_COLOR_STR_LIB_API
		#else
			#define CONSOLE_EXT_COLOR_STR_LIB_API
		#endif //!CONSOLE_EXT_COLOR_STR_EXPORTS
	#endif
#endif // !WIN32

#include <string>
#include "EnumColors.hpp"

namespace ConsoleExt
{
	/**
	 * @brief Colorize wide string
	 * @param wstr Wide string to be colorized
	 * @param fColor Foreground color string
	 * @return Colorized wide string, using ASCII code
	 */
	CONSOLE_EXT_COLOR_STR_LIB_API std::wstring ColorizeWstring(std::wstring wstr, ConsoleExt::ConsoleForegroundColor fColor);

	/**
	 * @brief Colorize wide string
	 * @param wstr Wide string to be colorized
	 * @param bColor Background color string
	 * @return Colorized wide string, using ASCII code
	 */
	CONSOLE_EXT_COLOR_STR_LIB_API std::wstring ColorizeWstring(std::wstring wstr, ConsoleExt::ConsoleBackgroundColor bColor);

	/**
	 * @brief Colorize wide string
	 * @param wstr Wide string to be colorized
	 * @param fColor Foreground color string
	 * @param bColor Background color string
	 * @return Colorized wide string, using ASCII code
	 */
	CONSOLE_EXT_COLOR_STR_LIB_API std::wstring ColorizeWstring(std::wstring wstr, ConsoleExt::ConsoleForegroundColor fColor, ConsoleExt::ConsoleBackgroundColor bColor);

	/**
	 * @brief Remove the colors from a wide string (background and foreground)
	 * @param wstr Wide string to be uncolored
	 * @return Return the uncolored string if is successful, otherwise will return the same string if failed
	 */
	CONSOLE_EXT_COLOR_STR_LIB_API std::wstring UnColorizeWstring(std::wstring wstr);
}

#endif // !COLOR_WSTRING_HPP