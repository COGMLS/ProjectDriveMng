#pragma once

#ifndef CONSOLE_EXT_STRING_EXT_CLASS_HPP
#define CONSOLE_EXT_STRING_EXT_CLASS_HPP

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
#include <vector>

#include "EnumColors.hpp"

#include "AsciiControls.hpp"
#include "AsciiSGR.hpp"

namespace ConsoleExt
{
	class CONSOLE_EXT_COLOR_STR_LIB_API String
	{
		private:

			std::string data;
			std::vector<ConsoleExt::SgrOptions> options;

			std::string applyAsciiOptions();
		
		public:

			String();

			String (std::string value);

			String (std::string value, std::vector<ConsoleExt::SgrOptions> options);

			~String();

			void setOption(ConsoleExt::SgrOptions option);

			bool hasOption(ConsoleExt::SgrOptions option);

			std::vector<ConsoleExt::SgrOptions> getOptions();

			std::string getRawString();

			std::string getFormattedString();

			void setRawString (std::string value);
	};
}

#endif // !CONSOLE_EXT_STRING_EXT_CLASS_HPP