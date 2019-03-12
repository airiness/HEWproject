/*
author:zhang ruisong
date:2019.3.9
pbullet class
*/
#pragma once
#include "GameObject.h"

constexpr auto BULLET_SPEED = 2;
class Bullet :
	public GameObject
{

public:
	Bullet(COORD, const std::string&, 
		std::unordered_map<std::string, Sprite*>&, 
		Scene&, MapInformation&,int belongActor_);
	~Bullet();

	virtual void update();
	void setBulletPos(COORD pos);
	bool isUse;
	bool isLeft;
	int bulletSpeed;
	void clearBulletMapInfo();

private:
	int belongActor;

};