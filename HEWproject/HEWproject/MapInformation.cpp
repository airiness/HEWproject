#include "MapInformation.h"

MapInformation::MapInformation(COORD mapSize_)
	:mapSize(mapSize_)
{
	vMapInfo.assign(mapSize_.X, std::vector<PixelProperty>(mapSize_.Y));
}

MapInformation::~MapInformation()
{
}

