#pragma once

#ifndef ARC_CONFIG_DATA_HPP
#define ARC_CONFIG_DATA_HPP

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

#include <string>
#include <memory>
#include <bitset>
#include <cctype>

namespace ArcLib
{
	namespace Datatypes
	{
		enum ArcConfigDataType : int
		{
			NOT_SET_CONFIG,
			NULL_CONFIG,
			STRING_CONFIG,
			INT_CONFIG,
			UINT_CONFIG,
			FLOAT_CONFIG,
			BOOLEAN_CONFIG,
			BINARY_CONFIG
		};

		class ConfigData
		{
			private:

				std::unique_ptr<std::string> valueStr;
				std::unique_ptr<long long> valueLl;
				std::unique_ptr<unsigned long long> valueUll;
				std::unique_ptr<double> valueF;
				std::unique_ptr<std::bitset<64>> valueBitSet;
				bool valueB;

				/***************************
				 * 0: Not set
				 * 1: Null
				 * 2: String
				 * 3: Integer
				 * 4: Unsigned Integer
				 * 5: Float
				 * 6: Boolean
				 * 7: Binary
				***************************/
				ArcConfigDataType type;

				bool isNull();

			public:

				ConfigData();

				ConfigData (short value);

				ConfigData (int value);

				ConfigData (long value);

				ConfigData (long long value);

				ConfigData (unsigned short value);

				ConfigData (unsigned int value);

				ConfigData (unsigned long value);

				ConfigData (unsigned long long value);

				ConfigData (float value);

				ConfigData (double value);

				ConfigData (std::string value);

				ConfigData (bool value);

				ConfigData (std::bitset<64> value);

				ConfigData (const ConfigData& other);

				ConfigData (ConfigData&& other) noexcept;

				~ConfigData();

				ConfigData& operator= (const ConfigData& other);

				ConfigData& operator= (ConfigData&& other) noexcept;

				bool resetData();

				bool isConfigDataSet();

				bool isNullValue();

				ArcConfigDataType getType();

				std::string getValueStr();

				bool getData (bool& value);

				bool getData (long long& value);

				bool getData (unsigned long long& value);

				bool getData (double& value);

				bool getData (std::string& value);

				bool getData (std::bitset<64>& value);

				bool setData (bool value);

				bool setData (long long value);

				bool setData (unsigned long long value);

				bool setData (double value);

				bool setData (std::string value);

				bool setData (std::bitset<64> value);
		};
	}
}

#endif // !ARC_CONFIG_DATA_HPP