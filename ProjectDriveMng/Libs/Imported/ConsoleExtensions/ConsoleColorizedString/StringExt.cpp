#include "StringExt.hpp"

std::string ConsoleExt::String::applyAsciiOptions()
{
    return std::string();
}

ConsoleExt::String::String()
{

}

ConsoleExt::String::String(std::string value)
{
	this->data = value;
}

ConsoleExt::String::String(std::string value, std::vector<ConsoleExt::SgrOptions> options)
{
	this->data = value;

	for (ConsoleExt::SgrOptions option : options)
	{
		switch (option)
		{
			case ConsoleExt::SgrOptions::ResetConsole:
			default:
			{
				if (option >= ConsoleExt::SgrOptions::StandardForegroundColor && option < ConsoleExt::SgrOptions::CustomForegroundColor)
				{
					option = ConsoleExt::SgrOptions::StandardForegroundColor;
				}

				if (option >= ConsoleExt::SgrOptions::StandardBackgroundColor && option < ConsoleExt::SgrOptions::CustomBackgroundColor)
				{
					option = ConsoleExt::SgrOptions::StandardBackgroundColor;
				}

				this->options.push_back(option);
				break;
			}
		}
	}
}

ConsoleExt::String::~String()
{
}

void ConsoleExt::String::setOption(ConsoleExt::SgrOptions option)
{
	if (!this->hasOption(option) && option != ConsoleExt::SgrOptions::ResetConsole)
	{
		if (option >= ConsoleExt::SgrOptions::StandardForegroundColor && option < ConsoleExt::SgrOptions::CustomForegroundColor)
		{
			option = ConsoleExt::SgrOptions::StandardForegroundColor;
		}

		if (option >= ConsoleExt::SgrOptions::StandardBackgroundColor && option < ConsoleExt::SgrOptions::CustomBackgroundColor)
		{
			option = ConsoleExt::SgrOptions::StandardBackgroundColor;
		}

		this->options.push_back(option);
	}
}

bool ConsoleExt::String::hasOption(ConsoleExt::SgrOptions option)
{
	for (ConsoleExt::SgrOptions i : this->options)
	{
		if (i == option)
		{
			return true;
		}
	}

	return false;
}

std::vector<ConsoleExt::SgrOptions> ConsoleExt::String::getOptions()
{
    return this->options;
}

std::string ConsoleExt::String::getRawString()
{
    return this->data;
}

std::string ConsoleExt::String::getFormattedString()
{
    return std::string();
}

void ConsoleExt::String::setRawString(std::string value)
{
	this->data = value;
}
