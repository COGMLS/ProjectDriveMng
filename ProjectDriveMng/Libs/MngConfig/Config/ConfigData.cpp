#include "ConfigData.hpp"

bool ArcLib::Config::ConfigData::isNull()
{
	if (this->type == ArcLib::Config::Datatypes::ArcConfigDataType::STRING_CONFIG)
	{
		std::string tmp;

		for (size_t i = 0; i < this->valueStr->size(); i++)
		{
			if (std::isalpha(this->valueStr->at(i)))
			{
				if (std::isupper(this->valueStr->at(i)))
				{
					tmp += std::tolower(this->valueStr->at(i));
				}
				else
				{
					tmp += this->valueStr->at(i);
				}
			}
		}

		if (tmp == "null")
		{
			return true;
		}
	}

    return false;
}

ArcLib::Config::ConfigData::ConfigData()
{
	this->resetData();
}

ArcLib::Config::ConfigData::ConfigData(short value)
{
	this->resetData();
	this->type = ArcLib::Config::Datatypes::ArcConfigDataType::INT_CONFIG;
	this->valueLl.reset(new long long);
	*this->valueLl = static_cast<long long>(value);
}

ArcLib::Config::ConfigData::ConfigData(int value)
{
	this->resetData();
	this->type = ArcLib::Config::Datatypes::ArcConfigDataType::INT_CONFIG;
	this->valueLl.reset(new long long);
	*this->valueLl = static_cast<long long>(value);
}

ArcLib::Config::ConfigData::ConfigData(long value)
{
	this->resetData();
	this->type = ArcLib::Config::Datatypes::ArcConfigDataType::INT_CONFIG;
	this->valueLl.reset(new long long);
	*this->valueLl = static_cast<long long>(value);
}

ArcLib::Config::ConfigData::ConfigData(long long value)
{
	this->resetData();
	this->type = ArcLib::Config::Datatypes::ArcConfigDataType::INT_CONFIG;
	this->valueLl.reset(new long long);
	*this->valueLl = static_cast<long long>(value);
}

ArcLib::Config::ConfigData::ConfigData(unsigned short value)
{
	this->resetData();
	this->type = ArcLib::Config::Datatypes::ArcConfigDataType::UINT_CONFIG;
	this->valueUll.reset(new unsigned long long);
	*this->valueUll = static_cast<unsigned long long>(value);
}

ArcLib::Config::ConfigData::ConfigData(unsigned int value)
{
	this->resetData();
	this->type = ArcLib::Config::Datatypes::ArcConfigDataType::UINT_CONFIG;
	this->valueUll.reset(new unsigned long long);
	*this->valueUll = static_cast<unsigned long long>(value);
}

ArcLib::Config::ConfigData::ConfigData(unsigned long value)
{
	this->resetData();
	this->type = ArcLib::Config::Datatypes::ArcConfigDataType::UINT_CONFIG;
	this->valueUll.reset(new unsigned long long);
	*this->valueUll = static_cast<unsigned long long>(value);
}

ArcLib::Config::ConfigData::ConfigData(unsigned long long value)
{
	this->resetData();
	this->type = ArcLib::Config::Datatypes::ArcConfigDataType::UINT_CONFIG;
	this->valueUll.reset(new unsigned long long);
	*this->valueUll = static_cast<unsigned long long>(value);
}

ArcLib::Config::ConfigData::ConfigData(float value)
{
	this->resetData();
	this->type = ArcLib::Config::Datatypes::ArcConfigDataType::FLOAT_CONFIG;
	this->valueF.reset(new double);
	*this->valueF = static_cast<double>(value);
}

ArcLib::Config::ConfigData::ConfigData(double value)
{
	this->resetData();
	this->type = ArcLib::Config::Datatypes::ArcConfigDataType::FLOAT_CONFIG;
	this->valueF.reset(new double);
	*this->valueF = value;
}

ArcLib::Config::ConfigData::ConfigData(std::string value)
{
	this->resetData();
	this->type = ArcLib::Config::Datatypes::ArcConfigDataType::STRING_CONFIG;
	this->valueStr.reset(new std::string);
	*this->valueStr = value;
	if (this->isNull())
	{
		this->type = ArcLib::Config::Datatypes::ArcConfigDataType::NULL_CONFIG;
	}
}

ArcLib::Config::ConfigData::ConfigData(bool value)
{
	this->resetData();
	this->type = ArcLib::Config::Datatypes::ArcConfigDataType::BOOLEAN_CONFIG;
	this->valueB = value;
}

ArcLib::Config::ConfigData::ConfigData(std::bitset<64> value)
{
	this->resetData();
	this->type = ArcLib::Config::Datatypes::ArcConfigDataType::BINARY_CONFIG;
	this->valueBitSet.reset(new std::bitset<64>);
	*this->valueBitSet = value;
}

ArcLib::Config::ConfigData::ConfigData(const ConfigData &other)
{
	this->resetData();
	this->type = other.type;
	switch (this->type)
	{
		case ArcLib::Config::Datatypes::ArcConfigDataType::NULL_CONFIG:
		case ArcLib::Config::Datatypes::ArcConfigDataType::STRING_CONFIG:
		{
			this->valueStr.reset(new std::string);
			*this->valueStr = *other.valueStr;
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::INT_CONFIG:
		{
			this->valueLl.reset(new long long);
			*this->valueLl = *other.valueLl;
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::UINT_CONFIG:
		{
			this->valueUll.reset(new unsigned long long);
			*this->valueUll = *other.valueUll;
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::FLOAT_CONFIG:
		{
			this->valueF.reset(new double);
			*this->valueF = *other.valueF;
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::BOOLEAN_CONFIG:
		{
			this->valueB = other.valueB;
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::BINARY_CONFIG:
		{
			this->valueBitSet.reset(new std::bitset<64>);
			*this->valueBitSet = *other.valueBitSet;
			break;
		}
		default:
		{
			break;
		}
	}
}

ArcLib::Config::ConfigData::ConfigData(ConfigData &&other) noexcept
{
	this->resetData();
	this->type = other.type;
	switch (this->type)
	{
		case ArcLib::Config::Datatypes::ArcConfigDataType::NULL_CONFIG:
		case ArcLib::Config::Datatypes::ArcConfigDataType::STRING_CONFIG:
		{
			this->valueStr.reset(new std::string);
			this->valueStr = std::move(other.valueStr);
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::INT_CONFIG:
		{
			this->valueLl.reset(new long long);
			this->valueLl = std::move(other.valueLl);
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::UINT_CONFIG:
		{
			this->valueUll.reset(new unsigned long long);
			this->valueUll = std::move(other.valueUll);
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::FLOAT_CONFIG:
		{
			this->valueF.reset(new double);
			this->valueF = std::move(other.valueF);
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::BOOLEAN_CONFIG:
		{
			this->valueB = other.valueB;
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::BINARY_CONFIG:
		{
			this->valueBitSet.reset(new std::bitset<64>);
			this->valueBitSet = std::move(other.valueBitSet);
			break;
		}
		default:
		{
			break;
		}
	}
}

ArcLib::Config::ConfigData::~ConfigData()
{
	this->resetData();
}

ArcLib::Config::ConfigData &ArcLib::Config::ConfigData::operator=(const ConfigData &other)
{
	if (this == &other)
	{
		return *this;
	}

	this->resetData();
	this->type = other.type;
	switch (this->type)
	{
		case ArcLib::Config::Datatypes::ArcConfigDataType::NULL_CONFIG:
		case ArcLib::Config::Datatypes::ArcConfigDataType::STRING_CONFIG:
		{
			this->valueStr.reset(new std::string);
			*this->valueStr = *other.valueStr;
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::INT_CONFIG:
		{
			this->valueLl.reset(new long long);
			*this->valueLl = *other.valueLl;
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::UINT_CONFIG:
		{
			this->valueUll.reset(new unsigned long long);
			*this->valueUll = *other.valueUll;
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::FLOAT_CONFIG:
		{
			this->valueF.reset(new double);
			*this->valueF = *other.valueF;
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::BOOLEAN_CONFIG:
		{
			this->valueB = other.valueB;
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::BINARY_CONFIG:
		{
			this->valueBitSet.reset(new std::bitset<64>);
			*this->valueBitSet = *other.valueBitSet;
			break;
		}
		default:
		{
			break;
		}
	}

	return *this;
}

ArcLib::Config::ConfigData &ArcLib::Config::ConfigData::operator=(ConfigData &&other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	this->resetData();
	this->type = other.type;
	switch (this->type)
	{
		case ArcLib::Config::Datatypes::ArcConfigDataType::NULL_CONFIG:
		case ArcLib::Config::Datatypes::ArcConfigDataType::STRING_CONFIG:
		{
			this->valueStr.reset(new std::string);
			this->valueStr = std::move(other.valueStr);
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::INT_CONFIG:
		{
			this->valueLl.reset(new long long);
			this->valueLl = std::move(other.valueLl);
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::UINT_CONFIG:
		{
			this->valueUll.reset(new unsigned long long);
			this->valueUll = std::move(other.valueUll);
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::FLOAT_CONFIG:
		{
			this->valueF.reset(new double);
			this->valueF = std::move(other.valueF);
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::BOOLEAN_CONFIG:
		{
			this->valueB = other.valueB;
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::BINARY_CONFIG:
		{
			this->valueBitSet.reset(new std::bitset<64>);
			this->valueBitSet = std::move(other.valueBitSet);
			break;
		}
		default:
		{
			break;
		}
	}

	return *this;
}

bool ArcLib::Config::ConfigData::resetData()
{
	try
	{
		this->type = ArcLib::Config::Datatypes::ArcConfigDataType::NOT_SET_CONFIG;
		this->valueB = false;
		this->valueStr.reset(nullptr);
		this->valueLl.reset(nullptr);
		this->valueUll.reset(nullptr);
		this->valueF.reset(nullptr);
		this->valueBitSet.reset(nullptr);

		return true;
	}
	catch(const std::exception&)
	{
    	return false;
	}
}

bool ArcLib::Config::ConfigData::isConfigDataSet()
{
	return this->type != ArcLib::Config::Datatypes::ArcConfigDataType::NOT_SET_CONFIG;
}

bool ArcLib::Config::ConfigData::isNullValue()
{
    return this->type == ArcLib::Config::Datatypes::ArcConfigDataType::NULL_CONFIG;
}

ArcLib::Config::Datatypes::ArcConfigDataType ArcLib::Config::ConfigData::getType()
{
    return this->type;
}

std::string ArcLib::Config::ConfigData::getValueStr()
{
	std::string valStr;

	switch (this->type)
	{
		case ArcLib::Config::Datatypes::ArcConfigDataType::NULL_CONFIG:
		case ArcLib::Config::Datatypes::ArcConfigDataType::STRING_CONFIG:
		{
			valStr = *this->valueStr;
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::INT_CONFIG:
		{
			try
			{
				valStr = std::to_string(*this->valueLl);
			}
			catch(const std::exception&)
			{
				
			}
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::UINT_CONFIG:
		{
			try
			{
				valStr = std::to_string(*this->valueUll);
			}
			catch(const std::exception&)
			{
				
			}
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::FLOAT_CONFIG:
		{
			try
			{
				valStr = std::to_string(*this->valueF);
			}
			catch(const std::exception&)
			{
				
			}
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::BOOLEAN_CONFIG:
		{
			try
			{
				valStr = std::to_string(this->valueB);
			}
			catch(const std::exception&)
			{
				
			}
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::BINARY_CONFIG:
		{
			try
			{
				valStr = this->valueBitSet->to_string();
			}
			catch(const std::exception&)
			{
				
			}
			break;
		}
		default:
		{
			break;
		}
	}

	return valStr;
}

bool ArcLib::Config::ConfigData::getData(bool &value)
{
	if (this->type == ArcLib::Config::Datatypes::ArcConfigDataType::BOOLEAN_CONFIG)
	{
		if (&value != nullptr)
		{
			try
			{
				value = this->valueB;
				return true;
			}
			catch(const std::exception&)
			{
				
			}
		}
	}

    return false;
}

bool ArcLib::Config::ConfigData::getData(long long &value)
{
    if (this->type == ArcLib::Config::Datatypes::ArcConfigDataType::INT_CONFIG)
	{
		if (&value != nullptr && this->valueLl.get() != nullptr)
		{
			try
			{
				value = *this->valueLl;
				return true;
			}
			catch(const std::exception&)
			{
				
			}
		}
	}

    return false;
}

bool ArcLib::Config::ConfigData::getData(unsigned long long &value)
{
    if (this->type == ArcLib::Config::Datatypes::ArcConfigDataType::UINT_CONFIG)
	{
		if (&value != nullptr && this->valueUll.get() != nullptr)
		{
			try
			{
				value = *this->valueUll;
				return true;
			}
			catch(const std::exception&)
			{
				
			}
		}
	}

    return false;
}

bool ArcLib::Config::ConfigData::getData(double &value)
{
     if (this->type == ArcLib::Config::Datatypes::ArcConfigDataType::FLOAT_CONFIG)
	{
		if (&value != nullptr && this->valueF.get() != nullptr)
		{
			try
			{
				value = *this->valueF;
				return true;
			}
			catch(const std::exception&)
			{
				
			}
		}
	}

    return false;
}

bool ArcLib::Config::ConfigData::getData(std::string &value)
{
	if (this->type == ArcLib::Config::Datatypes::ArcConfigDataType::STRING_CONFIG)
	{
		if (&value != nullptr && this->valueStr.get() != nullptr)
		{
			try
			{
				value = *this->valueStr;
				return true;
			}
			catch(const std::exception&)
			{
				
			}
		}
	}

    return false;
}

bool ArcLib::Config::ConfigData::getData(std::bitset<64> &value)
{
    if (this->type == ArcLib::Config::Datatypes::ArcConfigDataType::BINARY_CONFIG)
	{
		if (&value != nullptr && this->valueBitSet.get() != nullptr)
		{
			try
			{
				value = *this->valueBitSet;
				return true;
			}
			catch(const std::exception&)
			{
				
			}
		}
	}

    return false;
}

bool ArcLib::Config::ConfigData::setData(bool value)
{
	if (this->type == ArcLib::Config::Datatypes::ArcConfigDataType::BOOLEAN_CONFIG)
	{
		if (&value != nullptr)
		{
			try
			{
				this->valueB = value;
				return true;
			}
			catch(const std::exception&)
			{
				
			}
		}
	}

    return false;
}

bool ArcLib::Config::ConfigData::setData(long long value)
{
	if (this->type == ArcLib::Config::Datatypes::ArcConfigDataType::INT_CONFIG)
	{
		if (&value != nullptr && this->valueLl.get() != nullptr)
		{
			try
			{
				*this->valueLl = value;
				return true;
			}
			catch(const std::exception&)
			{
				
			}
		}
	}

    return false;
}

bool ArcLib::Config::ConfigData::setData(unsigned long long value)
{
    if (this->type == ArcLib::Config::Datatypes::ArcConfigDataType::UINT_CONFIG)
	{
		if (&value != nullptr && this->valueUll.get() != nullptr)
		{
			try
			{
				*this->valueUll = value;
				return true;
			}
			catch(const std::exception&)
			{
				
			}
		}
	}

    return false;
}

bool ArcLib::Config::ConfigData::setData(double value)
{
    if (this->type == ArcLib::Config::Datatypes::ArcConfigDataType::FLOAT_CONFIG)
	{
		if (&value != nullptr && this->valueF.get() != nullptr)
		{
			try
			{
				*this->valueF = value;
				return true;
			}
			catch(const std::exception&)
			{
				
			}
		}
	}

    return false;
}

bool ArcLib::Config::ConfigData::setData(std::string value)
{
    if (this->type == ArcLib::Config::Datatypes::ArcConfigDataType::STRING_CONFIG)
	{
		if (&value != nullptr && this->valueStr.get() != nullptr)
		{
			try
			{
				*this->valueStr = value;
				if (this->isNull())
				{
					this->type = ArcLib::Config::Datatypes::ArcConfigDataType::NULL_CONFIG;
				}
				return true;
			}
			catch(const std::exception&)
			{
				
			}
		}
	}

    return false;
}

bool ArcLib::Config::ConfigData::setData(std::bitset<64> value)
{
    if (this->type == ArcLib::Config::Datatypes::ArcConfigDataType::BINARY_CONFIG)
	{
		if (&value != nullptr && this->valueBitSet.get() != nullptr)
		{
			try
			{
				*this->valueBitSet = value;
				return true;
			}
			catch(const std::exception&)
			{
				
			}
		}
	}

    return false;
}
