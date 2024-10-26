#include "ArcConfig.hpp"

ArcLib::Config::ArcSettingsEntry::ArcSettingsEntry(std::string key)
{
	this->key = key;
	this->value = ArcLib::Config::ConfigData();
}

ArcLib::Config::ArcSettingsEntry::ArcSettingsEntry(std::string key, std::string value)
{
	this->key = key;

	ArcLib::Config::Datatypes::ArcConfigDataType type = ArcLib::Config::Datatypes::ArcConfigDataType::NOT_SET_CONFIG;

	long long tmpLl;
	unsigned long long tmpUll;
	double tmpF;
	bool tmpB;
	std::bitset<64> tmpBitset;

	try
	{
		tmpUll = std::stoull(value);
		type = ArcLib::Config::Datatypes::ArcConfigDataType::UINT_CONFIG;
	}
	catch(const std::exception&)
	{
		
	}

	try
	{
		tmpLl = std::stoll(value);
		type = ArcLib::Config::Datatypes::ArcConfigDataType::INT_CONFIG;
	}
	catch(const std::exception&)
	{
		
	}

	try
	{
		tmpF = std::stod(value);
		type = ArcLib::Config::Datatypes::ArcConfigDataType::FLOAT_CONFIG;
	}
	catch(const std::exception&)
	{
		
	}

	if (type == ArcLib::Config::Datatypes::ArcConfigDataType::NOT_SET_CONFIG)
	{
		std::string tmp;
		for (size_t i = 0; i < value.size(); i++)
		{
			if (std::isalpha(value[i]))
			{
				if (std::isupper(value[i]))
				{
					tmp += std::tolower(value[i]);
				}
				else
				{
					tmp += value[i];
				}
			}
		}

		if (tmp == "true")
		{
			tmpB = true;
			type = ArcLib::Config::Datatypes::ArcConfigDataType::BOOLEAN_CONFIG;
		}
		
		if (tmp == "false")
		{
			tmpB = false;
			type = ArcLib::Config::Datatypes::ArcConfigDataType::BOOLEAN_CONFIG;
		}
	}

	if (type == ArcLib::Config::Datatypes::ArcConfigDataType::NOT_SET_CONFIG)
	{
		try
		{
			tmpBitset = std::bitset<64>(value);
			type = ArcLib::Config::Datatypes::ArcConfigDataType::BINARY_CONFIG;
		}
		catch(const std::exception&)
		{
			
		}
	}

	if (type == ArcLib::Config::Datatypes::ArcConfigDataType::NOT_SET_CONFIG)
	{
		type = ArcLib::Config::Datatypes::ArcConfigDataType::STRING_CONFIG;
	}

	ArcLib::Config::ConfigData cfgVal;

	switch (type)
	{
		case ArcLib::Config::Datatypes::ArcConfigDataType::NULL_CONFIG:
		case ArcLib::Config::Datatypes::ArcConfigDataType::STRING_CONFIG:
		{
			cfgVal = ArcLib::Config::ConfigData(value);
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::INT_CONFIG:
		{
			cfgVal = ArcLib::Config::ConfigData(tmpLl);
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::UINT_CONFIG:
		{
			cfgVal = ArcLib::Config::ConfigData(tmpUll);
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::FLOAT_CONFIG:
		{
			cfgVal = ArcLib::Config::ConfigData(tmpF);
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::BOOLEAN_CONFIG:
		{
			cfgVal = ArcLib::Config::ConfigData(tmpB);
			break;
		}
		case ArcLib::Config::Datatypes::ArcConfigDataType::BINARY_CONFIG:
		{
			cfgVal = ArcLib::Config::ConfigData(tmpBitset);
			break;
		}
		default:
		{
			break;
		}
	}

	this->value = cfgVal;
}

ArcLib::Config::ArcSettingsEntry::ArcSettingsEntry(std::string key, ArcLib::Config::ConfigData value)
{
	this->key = key;
	this->value = value;
}

ArcLib::Config::ArcSettingsEntry::ArcSettingsEntry(const ArcLib::Config::ArcSettingsEntry &other)
{
	this->key = other.key;
	this->value = other.key;
}

ArcLib::Config::ArcSettingsEntry::ArcSettingsEntry(ArcLib::Config::ArcSettingsEntry &&other) noexcept
{
	this->key = std::move(other.key);
	this->value = std::move(other.value);
}

ArcLib::Config::ArcSettingsEntry::~ArcSettingsEntry()
{
}

ArcLib::Config::ArcSettingsEntry &ArcLib::Config::ArcSettingsEntry::operator=(const ArcLib::Config::ArcSettingsEntry &other)
{
	if (this == &other)
	{
		return *this;
	}

	this->key = other.key;
	this->value = other.value;

	return *this;
}

ArcLib::Config::ArcSettingsEntry &ArcLib::Config::ArcSettingsEntry::operator=(ArcLib::Config::ArcSettingsEntry &&other) noexcept
{
    if (this == &other)
	{
		return *this;
	}

	this->key = std::move(other.key);
	this->value = std::move(other.value);

	return *this;
}

std::string ArcLib::Config::ArcSettingsEntry::getKey()
{
    return this->key;
}

ArcLib::Config::ConfigData ArcLib::Config::ArcSettingsEntry::getValue()
{
    return this->value;
}

ArcLib::Config::Datatypes::ArcConfigDataType ArcLib::Config::ArcSettingsEntry::getType()
{
    return this->value.getType();
}

void ArcLib::Config::ArcSettingsEntry::setKey(std::string key)
{
	this->key = key;
}

void ArcLib::Config::ArcSettingsEntry::setValue(ArcLib::Config::ConfigData &value)
{
	this->value = value;
}

void ArcLib::Config::ArcSettings::updateConfigMap()
{
	// Clear the actual settings map
	this->settings.clear();

	std::string line;

	// Update the map:
	for (size_t i = 0; i < this->fileV.size(); i++)
	{
		line = this->fileV[i];

		if (!line.empty())
		{
			// Check if there is a key-value pair:

			size_t key_start = 0;
			size_t key_end = line.size() - 1;
			size_t value_start = 0;
			size_t value_end = line.size() - 1;
			bool hasEqualKey = false;
			bool foundKey = false;
			bool foundValue = false;

			for (size_t j = 0; j < line.size(); j++)
			{
				if (line[j] == '=')
				{
					if (j - 1 > 0)
					{
						key_end = i - 1;
					}

					if (j + 1 < line.size())
					{
						value_start = j + 1;
					}
					hasEqualKey = true;
					break;
				}
			}

			if (hasEqualKey)
			{
				std::string key;
				std::string value;

				key = line.substr(key_start, key_end);

				if (value_start > 0)
				{
					value = line.substr(value_start, line.size() - value_end);
				}

				ArcLib::Config::ArcSettingsEntry entry(key, value);

				this->settings.insert({entry.getKey(), entry});
			}
		}

		line.clear();
	}
}

ArcLib::Config::ArcSettings::ArcSettings(std::filesystem::path path)
{
	this->path = path;

	#ifdef _MSC_VER
	this->filename = this->path.filename().string()
	#else
	this->filename = this->path.filename();
	#endif // !_MSC_VER

	this->mode = std::ios::out;

	if (!std::filesystem::exists(this->path))
	{
		this->fs.open(this->path, this->mode);
		if (!fs.is_open())
		{
			std::string errMsg = "Invalid path or impossible to create file in: " + this->path.string();
			std::invalid_argument e(errMsg);
			throw e;
		}
		this->fs.close();
	}

	if (!std::filesystem::is_regular_file(this->path))
	{
		std::string errMsg = "Path is not a regular file: " + this->path.string();
		std::invalid_argument e(errMsg);
		throw e;
	}

	this->mode = std::ios::in | std::ios::out;

	this->fs.open(this->path, this->mode);

	if (this->fs.is_open())
	{
		this->loadFile();
	}
	else
	{
		std::string errMsg = "Path is not a regular file: " + this->path.string();
		std::invalid_argument e(errMsg);
		throw e;
	}
}

ArcLib::Config::ArcSettings::~ArcSettings()
{
	if (this->fs.is_open())
	{
		this->fs.close();
	}
}

bool ArcLib::Config::ArcSettings::findSetting(std::string key)
{
	return this->settings.contains(key);
}

ArcLib::Config::ArcSettingsEntry &ArcLib::Config::ArcSettings::getEntry(std::string key)
{
	return this->settings.at(key);
}

bool ArcLib::Config::ArcSettings::setEntry(ArcLib::Config::ArcSettingsEntry &entry)
{
	try
	{
		std::string key;
		key = entry.getKey();
		
		if (this->settings.contains(key))
		{
			auto p = &this->getEntry(key);
			*p = entry;
		}
		else
		{
			this->settings.insert({key, entry});
		}

		this->changed = true;

		return true;
	}
	catch(const std::exception& e)
	{
		return false;
	}
}

bool ArcLib::Config::ArcSettings::remove(std::string key)
{
    try
	{
		if (this->findSetting(key))
		{
			this->settings.erase(key);
			this->changed = true;
			return true;
		}

		return false;
	}
	catch(const std::exception&)
	{
		return false;
	}
	
}

int ArcLib::Config::ArcSettings::loadFile()
{
	if (!this->fs.is_open())
	{
		this->mode = std::ios::in | std::ios::out;
		fs.open(this->path, this->mode);
	}

	if (this->fs.is_open())
	{
		if (!this->fileV.empty())
		{
			this->fileV.clear();
		}

		std::string line;

		// Get the file lines:
		while (std::getline(fs, line))
		{
			// Check if the line is not empty:
			if (!line.empty())
			{
				// If the first character is space, remove it and test it again:
				while (line.starts_with(' '))
				{
					line = line.erase(0, 1);
				}

				// Make sure after removing all spaces does not make the line empty:
				if (!line.empty())
				{
					this->fileV.push_back(line);
				}
			}

			line.clear();
		}

		this->updateConfigMap();
		this->changed = false;
		fs.close();

    	return 0;	// Read and closed successfully the file
	}
	
	return 1;	// Fail to open
}

int ArcLib::Config::ArcSettings::saveFile()
{
	if (!this->fs.is_open())
	{
		this->mode = std::ios::in | std::ios::out;
		fs.open(this->path, this->mode);
	}

	if (this->fs.is_open())
	{
		fs.clear();

		std::string key;
		std::string value;
		std::string line;

		for (std::pair<const std::string, ArcLib::Config::ArcSettingsEntry>& entry : this->settings)
		{
			key.clear();
			value.clear();
			line.clear();

			key = entry.second.getKey();
			value = entry.second.getValue().getValueStr();
			line = key + "=" + value;

			fs << line << std::endl;
		}

		this->changed = false;
		fs.close();

    	return 0;	// Read and closed successfully the file
	}
	
	return 1;	// Fail to open
}
