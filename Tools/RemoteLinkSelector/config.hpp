#pragma once

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <filesystem>
#include <string>
#include <fstream>
#include <array>
#include <vector>

#include "definitions.hpp"
#include "directory.hpp"

/**
 * @brief Configuration Data Struct
 */
struct configData
{
	long version = 0;
	std::string description;
	std::string computer;
	std::string source;
};

/**
 * @brief Reference for Configuration Files
 */
extern std::array<std::string, 4> refConfigFile;

configData loadFile(std::filesystem::path path);

int saveFile (configData cfgData);

std::vector<std::filesystem::path> getConfigFiles();

#endif // !CONFIG_HPP