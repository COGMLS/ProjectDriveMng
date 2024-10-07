#pragma once

#ifndef CONSOLE_EXT_EXCEPTION_HPP
#define CONSOLE_EXT_EXCEPTION_HPP

#ifdef WIN32
	#ifdef CONSOLE_EXT_EXCEPTION_EXPORTS
		#define CONSOLE_EXT_EXCEPTION_LIB_API __declspec(dllexport)
	#else
		#define CONSOLE_EXT_EXCEPTION_LIB_API __declspec(dllimport)
	#endif //!CONSOLE_EXT_EXCEPTION_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef CONSOLE_EXT_EXCEPTION_EXPORTS
			#define CONSOLE_EXT_EXCEPTION_LIB_API __attribute__((visibility("default")))
		#else
			#define CONSOLE_EXT_EXCEPTION_LIB_API __attribute__((visibility("default")))
		#endif //!CONSOLE_EXT_EXCEPTION_EXPORTS
	#else
		#ifdef CONSOLE_EXT_EXCEPTION_EXPORTS
			#define CONSOLE_EXT_EXCEPTION_LIB_API
		#else
			#define CONSOLE_EXT_EXCEPTION_LIB_API
		#endif //!CONSOLE_EXT_EXCEPTION_EXPORTS
	#endif
#endif // !WIN32

#include <string>
#include <exception>

namespace ConsoleExt
{
	/**
	 * @class Console Extension Exception
	 * @brief The Console Extension Exception is a exception error class inherited from ISO C++ Exception, with similar Microsoft's implementation, using a additional constructor with message argument support. This class provide a unified solution over multiple platforms.
	 */
	class Exception : std::exception
	{
		private:

			std::string message;

		public:

			Exception() noexcept
			{

			}

			Exception(const char message[])
			{
				this->message = message;
			}

			Exception(const ConsoleExt::Exception& other) noexcept
			{
				this->message = other.message;
			}

			~Exception()
			{

			}

			ConsoleExt::Exception& operator=(const ConsoleExt::Exception& other) noexcept
			{
				if (this == &other)
				{
					return *this;
				}

				this->message = other.message;
				
				return *this;
			}

			virtual const char* what() const noexcept
			{
				return this->message.c_str();
			}
	};
}

#endif //!CONSOLE_EXT_EXCEPTION_HPP