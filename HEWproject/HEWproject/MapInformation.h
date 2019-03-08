#pragma once
#include<Windows.h>
#include<vector>
#include<unordered_map>
#include"PixelProperty.h"
#include"Scene.h"


class MapInformation
{
public:
	MapInformation(COORD , Scene& , 
		std::unordered_map<std::string, CHAR_INFO*> &);
	~MapInformation();

	void update();

	std::vector<std::vector<PixelProperty>> vMapInfo;
private:
	COORD mapSize;
	Scene* mapMainScene;
	std::unordered_map<std::string, CHAR_INFO*>* mapColorRes;
};

