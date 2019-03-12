#include "Bullet.h"


Bullet::Bullet(COORD position_, const std::string &name_,
	std::unordered_map<std::string, Sprite*>& msp_, Scene& sceneInfo_,
	MapInformation& mapInfo_,int belongActor_)
	:GameObject(position_, name_, msp_, sceneInfo_, mapInfo_),
	isUse(false),isLeft(true),bulletSpeed(BULLET_SPEED),belongActor(belongActor_)
{
} 

Bullet::~Bullet()
{
}


void Bullet::update()
{
	if (isUse)
	{
		objPosition.X += bulletSpeed;
		//collision ditect
		if (objPosition.X+objSprite.size_.X < 0 || objPosition.X>=sceneInfo->getScreenSize().X)
		{
			isUse = false;
		}



		//draw bullet
		for (size_t i = 0; i < objSprite.size_.X; i++)
		{
			for (size_t j = 0; j < objSprite.size_.Y; j++)
			{
				if (objSprite.isBlank_[j * objSprite.size_.X + i] == true)
				{
					if (objPosition.X+i <0 || objPosition.X+i >= sceneInfo->getScreenSize().X)
					{

					}
					else
					{
						sceneInfo->getSceneInfo()[(j + objPosition.Y)*  sceneInfo->getScreenSize().X + i + objPosition.X] = objSprite.charInfo_[j * objSprite.size_.X + i];
					}
				}
			}
		}
	}
}

void Bullet::setBulletPos(COORD pos)
{
	objPosition = pos;
}

void Bullet::clearBulletMapInfo()
{
}
