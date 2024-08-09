#pragma once

#ifndef PLACES_HPP
#define PLACES_HPP

#include <vector>
#include <filesystem>
#include <string>

#include "definitions.hpp"
#include "directory.hpp"
#include "config.hpp"

std::vector<std::filesystem::path> getPlaces();

std::filesystem::path getRemoteRefSymLink(std::vector<std::filesystem::path>& placesSymLinks);

int setRemoteRefSymLink (std::filesystem::path newRef);

#endif // !PLACES_HPP