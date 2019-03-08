#include "GameActor.h"

int GameActor::actorNum = 0;

GameActor::GameActor(COORD position_, const std::string &name_,
	std::unordered_map<std::string, Sprite*>& msp_, Scene& sceneInfo_,
	MapInformation& mapInfo_, CHAR_INFO actorColor_)
	:GameObject(position_, name_, msp_, sceneInfo_, mapInfo_), whitchActor(0),
	actorColor(actorColor_)
{
	actorNum++;
	whitchActor = actorNum;
	isEntity = true;
	for (size_t i = 0; i < pObjSprite->size_.X; i++)
	{
		for (size_t j = 0; j < pObjSprite->size_.Y; j++)
		{
			mapInfo->vMapInfo[position_.X + i][position_.Y + j].isBlock = true;

		}
	}
}

GameActor::~GameActor()
{
	actorNum--;
}

void GameActor::update()
{

	for (size_t i = 0; i < pObjSprite->size_.X; i++)
	{
		for (size_t j = 0; j < pObjSprite->size_.Y; j++)
		{
			if (pObjSprite->isBlank_[j * pObjSprite->size_.X + i] == true)
			{
				sceneInfo->getSceneInfo()[(j + objPosition.Y)*  sceneInfo->getScreenSize().X + i + objPosition.X]
					= pObjSprite->charInfo_[j * pObjSprite->size_.X + i];
			}
		}
	}

}

void GameActor::up()
{
	if (objPosition.Y > 0)
	{
		bool canMove = true;
		for (size_t i = 0; i < pObjSprite->size_.X; i++)
		{
			if (mapInfo->vMapInfo[objPosition.X + i][objPosition.Y - 1].isBlock)
			{
				canMove = false;
				break;
			}
		}
		if (canMove)
		{
			objPosition.Y--;
			for (size_t i = 0; i < pObjSprite->size_.X; i++)
			{
				mapInfo->vMapInfo[objPosition.X + i][objPosition.Y].isBlock = true;
				mapInfo->vMapInfo[objPosition.X + i][objPosition.Y + pObjSprite->size_.Y].isBlock = false;
			}
		}
	}
}

void GameActor::down()
{
	if (objPosition.Y + pObjSprite->size_.Y < sceneInfo->getScreenSize().Y)
	{
		bool canMove = true;
		for (size_t i = 0; i < pObjSprite->size_.X; i++)
		{
			if (mapInfo->vMapInfo[objPosition.X + i][objPosition.Y + pObjSprite->size_.Y].isBlock)
			{
				canMove = false;
				break;
			}
		}
		if (canMove)
		{
			objPosition.Y++;
			for (size_t i = 0; i < pObjSprite->size_.X; i++)
			{
				mapInfo->vMapInfo[objPosition.X + i][objPosition.Y - 1].isBlock = false;
				mapInfo->vMapInfo[objPosition.X + i][objPosition.Y + pObjSprite->size_.Y - 1].isBlock = true;
			}
		}
	}
}

void GameActor::left()
{
	if (objPosition.X > 0)
	{
		bool canMove = true;
		for (size_t i = 0; i < pObjSprite->size_.Y; i++)
		{
			if (mapInfo->vMapInfo[objPosition.X - 1][objPosition.Y + i].isBlock)
			{
				canMove = false;
				break;
			}
		}
		if (canMove)
		{
			objPosition.X--;
			for (size_t i = 0; i < pObjSprite->size_.Y; i++)
			{
				mapInfo->vMapInfo[objPosition.X][objPosition.Y + i].isBlock = true;
				mapInfo->vMapInfo[objPosition.X + pObjSprite->size_.X][objPosition.Y + i].isBlock = false;
			}
		}

	}

}

void GameActor::right()
{
	
	if (objPosition.X + pObjSprite->size_.X < sceneInfo->getScreenSize().X)
	{
		//if can move
		bool canMove = true;
		for (size_t i = 0; i < pObjSprite->size_.Y; i++)
		{
			if (mapInfo->vMapInfo[objPosition.X + pObjSprite->size_.X][objPosition.Y + i].isBlock)
			{
				canMove = false;
				break;
			}
		}
		if (canMove)
		{
			objPosition.X++;
			for (size_t i = 0; i < pObjSprite->size_.Y; i++)
			{
				mapInfo->vMapInfo[objPosition.X - 1][objPosition.Y + i].isBlock = false;
				mapInfo->vMapInfo[objPosition.X + pObjSprite->size_.X - 1][objPosition.Y + i].isBlock = true;
			}
		}
	}
}
