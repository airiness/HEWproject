#include "GameActor.h"


GameActor::GameActor(COORD position, Sprite &sp, const std::string &name)
	:GameObject(position,sp,name),velocity_(1)
{
}

GameActor::~GameActor()
{

}

void GameActor::update(Scene* screenInf)
{
	GameObject::update(screenInf);
	if (objPosition.X<0)
	{
		objPosition.X = 0;
	}
	if (objPosition.X > 130-pObjSprite->size_.X)
	{
		objPosition.X = 130 - pObjSprite->size_.X;
	}
}

void GameActor::jump()
{

}

void GameActor::left()
{
	objPosition.X--;
}

void GameActor::right()
{
	objPosition.X++;

}
