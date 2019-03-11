/*
author:zhang ruisong
date:2019.3.9
bullet class
*/
#pragma once
#include "GameObject.h"
class Bullet :
	public GameObject
{
	virtual void update();

public:
	Bullet(COORD, const std::string&, std::unordered_map<std::string, Sprite*>&, Scene&, MapInformation&);
	~Bullet();

private:
	bool direction;
	int speed;
};

