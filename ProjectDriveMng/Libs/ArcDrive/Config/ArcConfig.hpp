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
#include <stdexcept>

#include "ConfigData.hpp"

namespace ArcLib
{
	namespace Config
	{
		class ARC_LIB_API ArcSettingsEntry
		{
			private:

				std::string key;
				ArcLib::Datatypes::ConfigData value;
			
			public:

				ArcSettingsEntry (std::string key);

				ArcSettingsEntry (std::string key, std::string value);

				ArcSettingsEntry (std::string key, ArcLib::Datatypes::ConfigData value);

				ArcSettingsEntry (const ArcLib::Config::ArcSettingsEntry& other);

				ArcSettingsEntry (ArcLib::Config::ArcSettingsEntry&& other) noexcept;

				~ArcSettingsEntry();

				ArcLib::Config::ArcSettingsEntry& operator= (const ArcLib::Config::ArcSettingsEntry& other);

				ArcLib::Config::ArcSettingsEntry& operator= (ArcLib::Config::ArcSettingsEntry&& other) noexcept;

				std::string getKey();

				ArcLib::Datatypes::ConfigData getValue();

				ArcLib::Datatypes::ArcConfigDataType getType();

				void setKey (std::string key);

				void setValue (ArcLib::Datatypes::ConfigData& value);
		};

		class ARC_LIB_API ArcSettings
		{
			private:

				std::fstream fs;
				std::ios::openmode mode;
				std::string filename;
				std::filesystem::path path;
				std::vector<std::string> fileV;
				std::map<std::string, ArcLib::Config::ArcSettingsEntry> settings;
				bool changed;

				void updateConfigMap();

			public:

				ArcSettings (std::filesystem::path path);

				~ArcSettings();

				bool findSetting (std::string key);

				ArcSettingsEntry getEntry (std::string key);

				bool setEntry (ArcSettingsEntry& entry);

				bool remove (std::string key);

				int loadFile();

				int saveFile();
		};
	}
}

#endif // !ARC_CONFIG_HPP