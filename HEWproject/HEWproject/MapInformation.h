#pragma once
#include<Windows.h>
#include<vector>
#include"PixelProperty.h"

class MapInformation
{
public:
	MapInformation(COORD);
	~MapInformation();

	std::vector<std::vector<PixelProperty>> vMapInfo;
private:
	COORD mapSize;
};

