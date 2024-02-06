#pragma once

#ifndef CONSOLE_EXTENSIONS_LIBRARY_DEFINE_HPP
#define CONSOLE_EXTENSIONS_LIBRARY_DEFINE_HPP

	#ifdef CONSOLEEXTENSIONS_EXPORTS
		#define CONSOLE_EXTENSIONS_API __declspec(dllexport)
	#else
		#define CONSOLE_EXTENSIONS_API __declspec(dllimport)
	#endif //!CONSOLEEXTENSIONS_EXPORT

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)

#endif //!CONSOLE_EXTENSIONS_LIBRARY_DEFINE_HPP