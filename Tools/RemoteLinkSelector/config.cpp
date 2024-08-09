#include "config.hpp"

std::array<std::string, 4> refConfigFile = 
{
	"version=",
	"description=",
	"computer=",
	"source="
};

configData loadFile(std::filesystem::path path)
{
	configData cfgData;

	if (std::filesystem::exists(path))
	{
		if (std::filesystem::is_regular_file(path))
		{
			std::fstream fs(path.string(), std::ios_base::openmode::_S_in);

			if (fs.is_open())
			{
				bool getComputerInfo = false;
				bool getSourceInfo = false;
				std::string tmp;
				while(std::getline(fs, tmp))
				{
					if (tmp.starts_with(refConfigFile[0]))
					{
						tmp = tmp.substr(refConfigFile[0].size());

						try
						{
							long tmpL = std::stol(tmp);

							if (tmpL > 0)
							{
								cfgData.version = tmpL;
							}
							else
							{
								cfgData.version = -1;
							}
						}
						catch(const std::exception&)
						{
							cfgData.version = -2;
						}
					}

					if (tmp.starts_with(refConfigFile[1]))
					{
						cfgData.description = tmp.substr(refConfigFile[1].size());
					}

					if (tmp.starts_with(refConfigFile[2]))
					{
						cfgData.computer = tmp.substr(refConfigFile[2].size());
						getComputerInfo = true;
					}

					if (tmp.starts_with(refConfigFile[3]))
					{
						cfgData.source = tmp.substr(refConfigFile[3].size());
						getSourceInfo = true;
					}
				}

				fs.close();

				if (!(getComputerInfo || getSourceInfo))
				{
					cfgData.version = -4;
				}
			}
		}
	}

    return cfgData;
}

int saveFile(configData cfgData)
{
	std::filesystem::path path = getRemoteLinkSelectorPath();

	if (!path.empty() && !cfgData.computer.empty())
	{
		std::string fileName = cfgData.computer + REMOTE_CONFIG_EXT;

		path = path / fileName;

		bool fileCreated = false;
		std::fstream fs;
		std::ios_base::openmode openMode;

		if (std::filesystem::exists(path))
		{
			openMode = std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_trunc;
		}
		else
		{
			fileCreated = true;
			openMode = std::ios_base::openmode::_S_out;
		}

		fs.open(path.string(), openMode);

		if (fs.is_open())
		{
			std::array<std::string, 4> fileContent;

			fileContent[0] = refConfigFile[0] + std::to_string(cfgData.version);
			fileContent[1] = refConfigFile[1] + cfgData.description;
			fileContent[2] = refConfigFile[2] + cfgData.computer;
			fileContent[3] = refConfigFile[3] + cfgData.source;

			for (size_t i = 0; i < fileContent.size(); i++)
			{
				if (i + 1 == fileContent.size())
				{
					fs << fileContent[i];
				}
				else
				{
					fs << fileContent[i] << std::endl;
				}
			}

			fs.close();

			if (fileCreated)
			{
				return 1;
			}

			return 0;
		}

		return -2;
	}

	return -1;
}

std::vector<std::filesystem::path> getConfigFiles()
{
    std::filesystem::path configDir = getRemoteLinkSelectorPath();

	if (configDir.empty())
	{
		return std::vector<std::filesystem::path>();
	}

	std::vector<std::filesystem::path> cfgFiles;

	for (std::filesystem::directory_entry d : std::filesystem::directory_iterator(configDir))
	{
		if (d.path().extension() == REMOTE_CONFIG_EXT)
		{
			cfgFiles.push_back(d.path());
		}
	}

	return cfgFiles;
}
