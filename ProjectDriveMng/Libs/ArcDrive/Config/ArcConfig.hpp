#pragma once

#ifndef ARC_CONFIG_HPP
#define ARC_CONFIG_HPP

#ifdef WIN32
	#ifdef ARC_CONFIG_LIB_EXPORTS
		#define ARC_LIB_API __declspec(dllexport)
	#else
		#define ARC_LIB_API __declspec(dllimport)
	#endif //!ARC_CONFIG_LIB_EXPORTS

	#pragma warning (disable : 4251)
	#pragma warning (disable : 4273)
#else
	#if __GNUC__ >= 4
		#ifdef ARC_CONFIG_LIB_EXPORTS
			#define ARC_LIB_API __attribute__((visibility("default")))
		#else
			#define ARC_LIB_API __attribute__((visibility("default")))
		#endif //!ARC_CONFIG_LIB_EXPORTS
	#else
		#ifdef ARC_CONFIG_LIB_EXPORTS
			#define ARC_LIB_API
		#else
			#define ARC_LIB_API
		#endif //!ARC_CONFIG_LIB_EXPORTS
	#endif
#endif // !WIN32

#include <filesystem>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <thread>
#include <array>
#include <map>

namespace ArcLib
{
	namespace Config
	{
		enum ArcSettingsType
		{
			NULL_CONFIG,
			STRING_CONFIG,
			INT_CONFIG,
			LONG_CONFIG,
			FLOAT_CONFIG,
			DOUBLE_CONFIG,
			BINARY_CONFIG,
			BOOLEAN_CONFIG
		};

		class ARC_LIB_API ArcSettingsEntry
		{
			private:

				std::string name;
				std::string value;
				ArcSettingsType type;
			
			public:

				ArcSettingsEntry (std::string name, std::string value);

				ArcSettingsEntry (const ArcLib::Config::ArcSettingsEntry& other);

				ArcSettingsEntry (ArcLib::Config::ArcSettingsEntry&& other) noexcept;

				~ArcSettingsEntry();

				std::string getName();

				std::string getValue();

				ArcSettingsEntry getType();
		};

		class ARC_LIB_API ArcSettings
		{
			private:

				std::string name;
				std::filesystem::path path;
				std::vector<std::string> fileV;
				std::map<std::string, ArcSettingsEntry> settings;

			public:

				ArcSettings();

				ArcSettings (std::filesystem::path path);

				~ArcSettings();
		};
	}
}

#endif // !ARC_CONFIG_HPP