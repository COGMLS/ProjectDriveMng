#pragma once

#ifndef COLOR_STRING_HPP
#define COLOR_STRING_HPP

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
#include "AsciiControls.hpp"
#include "AsciiSGR.hpp"
#include "ConsoleDataTypes.hpp"

namespace ConsoleExt
{
	/**
	 * @brief Colorize string
	 * @param str String to be colorized
	 * @param fColor Foreground color string
	 * @return Colorized string, using ASCII code
	 */
	CONSOLE_EXT_COLOR_STR_LIB_API std::string ColorizeString(std::string str, ConsoleExt::ConsoleForegroundColor fColor);

	/**
	 * @brief Colorize string
	 * @param str String to be colorized
	 * @param bColor Background color string
	 * @return Colorized string, using ASCII code
	 */
	CONSOLE_EXT_COLOR_STR_LIB_API std::string ColorizeString(std::string str, ConsoleExt::ConsoleBackgroundColor bColor);

	/**
	 * @brief Colorize string
	 * @param str String to be colorized
	 * @param fColor Foreground color string
	 * @param bColor Background color string
	 * @return Colorized string, using ASCII code
	 */
	CONSOLE_EXT_COLOR_STR_LIB_API std::string ColorizeString(std::string str, ConsoleExt::ConsoleForegroundColor fColor, ConsoleExt::ConsoleBackgroundColor bColor);

	/**
	 * @brief Colorize string
	 * @param str String to be colorized
	 * @param color Hexadecimal color (unsigned int)
	 * @param background Define to apply the color to the background
	 * @return Colorized string, using ASCII code
	 * @note The integer is used as hexadecimal color using the traditional RGB (0xRRGGBB)
	 */
	CONSOLE_EXT_COLOR_STR_LIB_API std::string ColorizeString(std::string str, unsigned int color, bool background);

	/**
	 * @brief Colorize string
	 * @param str String to be colorized
	 * @param color ColorData structure
	 * @param background Define to apply the color to the background
	 * @return Colorized string, using ASCII code
	 */
	CONSOLE_EXT_COLOR_STR_LIB_API std::string ColorizeString(std::string str, ConsoleExt::ColorData color, bool background);

	/**
	 * @brief Colorize string
	 * @param str String to be colorized
	 * @param fColor Foreground color with hexadecimal value.
	 * @param bColor Background color with hexadecimal value.
	 * @return Colorized string, using ASCII code
	 * @note The integer is used as hexadecimal color using the traditional RGB (0xRRGGBB)
	 */
	CONSOLE_EXT_COLOR_STR_LIB_API std::string ColorizeString(std::string str, unsigned int fColor, unsigned int bColor);

	/**
	 * @brief Colorize string
	 * @param str String to be colorized
	 * @param fColor Foreground Color Data structure
	 * @param bColor Background Color Data structure
	 * @return Colorized string, using ASCII code
	 */
	CONSOLE_EXT_COLOR_STR_LIB_API std::string ColorizeString(std::string str, ConsoleExt::ColorData fColor, ConsoleExt::ColorData bColor);

	/**
	 * @brief Remove the colors from a string (background and foreground)
	 * @param str String to be uncolored
	 * @return Return the uncolored string if is successful, otherwise will return the same string if failed
	 * @note This function was not designed to remove the color on strings with custom RGB colors
	 */
	CONSOLE_EXT_COLOR_STR_LIB_API std::string UnColorizeString(std::string str);
}

#endif // !COLOR_STRING_HPP