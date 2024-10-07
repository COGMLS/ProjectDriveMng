#pragma once

#ifndef CONSOLE_EXT_CONSOLE_CONTROLS_HPP
#define CONSOLE_EXT_CONSOLE_CONTROLS_HPP

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

#include "AsciiControls.hpp"
#include "LowLevelControls.hpp"

#endif // !CONSOLE_EXT_CONSOLE_CONTROLS_HPP