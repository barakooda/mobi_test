#ifndef SAVEMAPDATA_H
#define SAVEMAPDATA_H

#include <filesystem>
#include "MapData.h"

bool saveMapDataToFile(const MapData& mapData, const std::filesystem::path& filePath);

#endif // SAVEMAPDATA_H
