#pragma once

#ifndef PLACES_HPP
#define PLACES_HPP

#include <vector>
#include <filesystem>
#include <string>

#include "definitions.hpp"
#include "directory.hpp"
#include "config.hpp"

/// @brief Get the links available in Places directory:
std::vector<std::filesystem::path> getPlaces();

/// @brief Get the path to reference symbolic link for remote access
std::filesystem::path getRemoteRefSymLink(std::vector<std::filesystem::path>& placesSymLinks);

/**
 * @brief Set a remote reference symbolic link
 * @param newRef Path to new reference
 * @return -1 on exceptions
 * @return 0 on successful operations
 * @return 1 if Places doesn't exist
 * @return 2 if fail to create the symbolic link without exception
 */
int setRemoteRefSymLink (std::filesystem::path newRef);

#endif // !PLACES_HPP