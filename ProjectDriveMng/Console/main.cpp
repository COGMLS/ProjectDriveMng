#include <iostream>

#include "VersionDataBase.hpp"

#include "../Libs/Imported/VersionLib/VersionLib.hpp"

int main (int argc, const char* argv[], const char* argp[])
{
	std::cout << "Project Drive Manager Console\t" << ProjectDriveMng_vInfo.getVersionStr(false, false) << std::endl;

	std::cout << std::endl << "Library versions:" << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;

	std::cout << "  Console Extensions: " << ConsoleExt_vInfo.getVersionStr() << std::endl;
	std::cout << "  LoggerLib:          " << LoggerLib_vInfo.getVersionStr() << std::endl;
	std::cout << "  VersionLib:         " << VersionLib_vInfo.getVersionStr() << std::endl;

	return 0;
}