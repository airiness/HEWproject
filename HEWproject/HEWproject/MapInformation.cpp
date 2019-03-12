#include "MapInformation.h"

MapInformation::MapInformation(COORD mapSize_,Scene&scene,
	std::unordered_map<std::string, CHAR_INFO*> &  acolors)
	:mapSize(mapSize_),mapMainScene(&scene),mapColorRes(&acolors)
{
	init();
}



MapInformation::~MapInformation()
{
}

void MapInformation::init()
{
	vMapInfo.assign(mapSize.X, std::vector<PixelProperty>(mapSize.Y));

}

void MapInformation::update()
{
	for (size_t i = 0; i < mapSize.X; i++)
	{
		for (size_t j = 0; j < mapSize.Y; j++)
		{
			if (vMapInfo[i][j].belongWho!=0)
			{
				std::string colorName = { "player" };
				colorName = colorName + std::to_string(vMapInfo[i][j].belongWho) + "color";
				mapMainScene->getSceneInfo()[j*mapSize.X+ i] = *mapColorRes->find(colorName)->second;
			}

		}
	}
}



