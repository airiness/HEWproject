#include "Bullet.h"

void Bullet::update()
{
}

Bullet::Bullet(COORD position_, const std::string &name_,
	std::unordered_map<std::string, Sprite*>& msp_, Scene& sceneInfo_,
	MapInformation& mapInfo_)
	:GameObject(position_, name_, msp_, sceneInfo_, mapInfo_)
{
}

Bullet::~Bullet()
{
}
