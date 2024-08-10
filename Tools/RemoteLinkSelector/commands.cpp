#include "commands.hpp"

cmd::cmd(std::string cmd)
{
	this->cmdValue = cmd;
	this->type = CMDTYPE::UNKNOWN_CMD;

	for (size_t i = 0; i < cmdArr.size(); i++)
	{
		if (cmdArr[i] == this->cmdValue)
		{
			this->type = static_cast<CMDTYPE>(i);
		}
	}

	if (this->type == CMDTYPE::UNKNOWN_CMD)
	{
		this->type = CMDTYPE::ARGUMENT;
	}
}

cmd::cmd(const cmd &other)
{
	this->cmdValue = other.cmdValue;
	this->type = other.type;
}

cmd::cmd(cmd &&other) noexcept
{
	this->cmdValue = std::move(other.cmdValue);
	this->type = std::move(other.type);
}

cmd::~cmd()
{

}

cmd &cmd::operator=(const cmd &other)
{
    this->cmdValue = other.cmdValue;
	this->type = other.type;

	return *this;
}

cmd &cmd::operator=(cmd &&other) noexcept
{
    this->cmdValue = std::move(other.cmdValue);
	this->type = std::move(other.type);

	return *this;
}

bool operator==(cmd &lhs, cmd &rhs)
{
	bool cmdValueEq = lhs.cmdValue == rhs.cmdValue;
	bool cmdTypeEq = lhs.type == rhs.type;

    return cmdValueEq && cmdTypeEq;
}

bool operator==(cmd &other, CMDTYPE type)
{
    return other.type == type;
}

std::ostream &operator<<(std::ostream &os, const cmd &obj)
{
	std::string str;

	str += "[" + std::to_string(static_cast<int>(obj.type)) + "]" + obj.cmdValue;

	os << str;

	return os;
}

std::string cmd::getValue()
{
    return this->cmdValue;
}

CMDTYPE cmd::getType()
{
    return this->type;
}

std::vector<cmd> getCmdList(std::string cmdLine)
{
    std::vector<cmd> cmdList;

	if (cmdLine.empty())
	{
		return cmdList;
	}

	bool isOpenQuote = false;
	bool isCloseQuote = false;
	size_t openQuotePos = 0;
	size_t closeQuotePos = 0;

	char c = '\0';
	std::string tmp;

	for (size_t i = 0; i < cmdLine.size(); i++)
	{
		c = cmdLine.at(i);

		if (c == ' ')
		{
			if (isOpenQuote && isCloseQuote)
			{
				if (!tmp.empty())
				{
					cmdList.push_back(tmp);
				}

				isOpenQuote = false;
				isCloseQuote = false;
				openQuotePos = 0;
				closeQuotePos = 0;
				tmp.clear();
			}

			if (!openQuotePos && !isCloseQuote)
			{
				if (!tmp.empty())
				{
					cmdList.push_back(tmp);
				}

				tmp.clear();
			}
		}

		if (c == '"' && isOpenQuote && !isCloseQuote)
		{
			isCloseQuote = true;
			closeQuotePos = i;
		}

		if (c == '"' && !isOpenQuote && !isCloseQuote)
		{
			isOpenQuote = true;
			openQuotePos = i;
		}

		if (isOpenQuote)
		{
			tmp += c;
		}
		else
		{
			if (c != ' ')
			{
				tmp += c;
			}
		}
	}

	if (!tmp.empty())
	{
		cmdList.push_back(tmp);
		tmp.clear();
	}

	return cmdList;
}
