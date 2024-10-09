#include "VersionDataBase.hpp"

const std::vector<VersionLib::VersionData> getVersionDb()
{
    std::vector<VersionLib::VersionData> db;

	//VersionLib::VersionData ConsoleExt_vInfo(ConsoleExt::getVersionStr(ConsoleExt::getLibVersion(), true, true));
	//VersionLib::VersionData LoggerLib_vInfo(LoggerLib::getVersionStr(LoggerLib::getLibVersion(), true, true));
	//VersionLib::VersionData VersionLib_vInfo(VersionLib::internalVersionData);
	//db.push_back(ConsoleExt_vInfo);
	//db.push_back(LoggerLib_vInfo);
	//db.push_back(VersionLib_vInfo);

	for (size_t i = 0; i < verMinDb.size(); i++)
	{
		if (verMinDb[i][0] == "Console Extensions")
		{
			db.push_back(ConsoleExt::getVersionStr(ConsoleExt::getLibVersion(), true, true));
		}

		if (verMinDb[i][0] == "LoggerLib")
		{
			db.push_back(LoggerLib::getVersionStr(LoggerLib::getLibVersion(), true, true));
		}

		if (verMinDb[i][0] == "VersionLib")
		{
			db.push_back(VersionLib::internalVersionData());
		}
	}

	return db;
}

const std::vector<VersionLib::VersionData> getMinVersionDb()
{
    std::vector<VersionLib::VersionData> db;

	//VersionLib::VersionData ConsoleExt_vInfo(ConsoleExt::getVersionStr(ConsoleExt::getLibVersion(), true, true));
	//VersionLib::VersionData LoggerLib_vInfo(LoggerLib::getVersionStr(LoggerLib::getLibVersion(), true, true));
	//VersionLib::VersionData VersionLib_vInfo(VersionLib::internalVersionData);
	//db.push_back(ConsoleExt_vInfo);
	//db.push_back(LoggerLib_vInfo);
	//db.push_back(VersionLib_vInfo);

	for (size_t i = 0; i < verMinDb.size(); i++)
	{
		if (verMinDb[i][0] == "Console Extensions")
		{
			db.push_back(VersionLib::VersionData(verMinDb[i][1]));
		}

		if (verMinDb[i][0] == "LoggerLib")
		{
			db.push_back(VersionLib::VersionData(verMinDb[i][1]));
		}

		if (verMinDb[i][0] == "VersionLib")
		{
			db.push_back(VersionLib::VersionData(verMinDb[i][1]));
		}
	}

	return db;
}

const std::vector<std::array<std::string, 4>> testLibCompat(const std::vector<VersionLib::VersionData> &actualVer)
{
    std::vector<std::array<std::string, 4>> verCompatStatus;

	auto minVer = getMinVersionDb();

	if (verCompatStatus.size() != actualVer.size())
	{
		return verCompatStatus;	// Return an empty list of compatibility check.
	}

	for (size_t i = 0; i < verMinDb.size(); i++)
	{
		VersionLib::VersionData v1 = minVer.at(i);
		VersionLib::VersionData v2 = actualVer.at(i);

		std::array<std::string, 4> status;

		status[0] = verMinDb[i][0];
		status[1] = v1.getVersionStr();
		status[2] = v2.getVersionStr();

		if (v1 <= v2)
		{
			status[3] = "Compatible";
		}
		else
		{
			status[3] = "Not compatible";
		}
	}

	return verCompatStatus;
}
