#include "GameActor.h"

int GameActor::actorNum = 0;

GameActor::GameActor(COORD position, Sprite &sp, const std::string &name)
	:GameObject(position,sp,name),velocity_(1),whitchActor(0)
{
	actorNum++;
	whitchActor = actorNum;
}

GameActor::~GameActor()
{
	actorNum--;
}


void GameActor::update(Scene* screenInf)
{
	GameObject::update(screenInf);

}

void GameActor::up()
{
	if (objPosition.Y > 0)
	{
		objPosition.Y--;

	}
}

void GameActor::down()
{
	if (objPosition.Y + pObjSprite->size_.Y < 40)
	{
		objPosition.Y++;

	}
}

void GameActor::left()
{
	if (objPosition.X > 0)
	{
		objPosition.X--;
	}

}

void GameActor::right()
{
	if (objPosition.X + pObjSprite->size_.X <160)
	{
		objPosition.X++;
	}

}
