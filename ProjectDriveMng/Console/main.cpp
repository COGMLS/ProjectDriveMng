#include <iostream>

#include "VersionDataBase.hpp"

#include "../Libs/Imported/VersionLib/VersionLib.hpp"

int main (int argc, const char* argv[], const char* argp[])
{
	const std::vector<VersionLib::VersionData> verDb = getVersionDb();
	auto verStatus = testLibCompat(verDb);

	std::cout << "Project Drive Manager Console\t" << ProjectDriveMng_vInfo.getVersionStr(false, false) << std::endl;

	std::cout << std::endl << "Library versions:" << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;
	std::cout << "Library | Minimum Version | Actual Version | Status" << std::endl;

	for (size_t i = 0; i < verStatus.size(); i++)
	{
		std::cout << verStatus[i][0] << " | " << verStatus[i][1] << " | " << verStatus[i][2] << " | " << verStatus[i][3] << std::endl;
	}

	return 0;
}