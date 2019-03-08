#include "GameActor.h"

int GameActor::actorNum = 0;

GameActor::GameActor(COORD position_, const std::string &name_,
	std::unordered_map<std::string, Sprite*>& msp_, Scene& sceneInfo_,
	MapInformation& mapInfo_, std::unordered_map<std::string, CHAR_INFO*>& color_)
	:GameObject(position_, name_, msp_, sceneInfo_, mapInfo_), whitchActor(0),
	actorColor(nullptr),colorRes(&color_)
{
	actorNum++;
	whitchActor = actorNum;
	isEntity = true;
	for (size_t i = 0; i < pObjSprite->size_.X; i++)
	{
		for (size_t j = 0; j < pObjSprite->size_.Y; j++)
		{
			mapInfo->vMapInfo[position_.X + i][position_.Y + j].isBlock = true;
			mapInfo->vMapInfo[position_.X + i][position_.Y + j].belongWho = whitchActor;
		}
	}
	std::string colorName = { "player" };
	colorName = colorName + std::to_string(whitchActor) + "color";
	actorColor = colorRes->find(colorName)->second;
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
			else
			{

			}
		}
	}

}

//when actor move up
void GameActor::up()
{
	if (objPosition.Y > 0)
	{
		bool canMove = true;
		bool canDraw = false;
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
			for (size_t i = 0; i < pObjSprite->size_.X; i++)
			{
				if (mapInfo->vMapInfo[objPosition.X +i][objPosition.Y -1].belongWho != whitchActor)
				{
					canDraw = true;
					break;
				}
			}
			objPosition.Y--;
			for (size_t i = 0; i < pObjSprite->size_.X; i++)
			{
				mapInfo->vMapInfo[objPosition.X + i][objPosition.Y].isBlock = true;
				mapInfo->vMapInfo[objPosition.X + i][objPosition.Y + pObjSprite->size_.Y].isBlock = false;
			}
			if (canDraw)
			{
				inkPower -= 2;
				if (inkPower<0)
				{
					inkPower = 0;
				}
				else
				{
					for (size_t i = 0; i < pObjSprite->size_.X; i++)
					{
						mapInfo->vMapInfo[objPosition.X + i][objPosition.Y].belongWho = whitchActor;
					}
				}

			}
		}
	}
}

//when actor move to down
void GameActor::down()
{
	if (objPosition.Y + pObjSprite->size_.Y < sceneInfo->getScreenSize().Y)
	{
		bool canMove = true;
		bool canDraw = false;
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
			for (size_t i = 0; i < pObjSprite->size_.X; i++)
			{
				if (mapInfo->vMapInfo[objPosition.X + i][objPosition.Y + pObjSprite->size_.Y].belongWho != whitchActor)
				{
					canDraw = true;
					break;
				}
			}
			objPosition.Y++;
			for (size_t i = 0; i < pObjSprite->size_.X; i++)
			{
				mapInfo->vMapInfo[objPosition.X + i][objPosition.Y - 1].isBlock = false;
				mapInfo->vMapInfo[objPosition.X + i][objPosition.Y + pObjSprite->size_.Y - 1].isBlock = true;
			}
			if (canDraw)
			{
				inkPower -= 2;
				if (inkPower<0)
				{
					inkPower = 0;
				}
				else
				{
					for (size_t i = 0; i < pObjSprite->size_.X; i++)
					{
						mapInfo->vMapInfo[objPosition.X + i][objPosition.Y + pObjSprite->size_.Y - 1].belongWho = whitchActor;
					}
				}
			}
		}
	}
}

void GameActor::left()
{
	std::string spname = { "player" };
	spname = spname + std::to_string(whitchActor) + "left";
	pObjSprite = uomSprites->find(spname)->second;
	if (objPosition.X > 0)
	{
		bool canMove = true;
		bool canDraw = false;
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
			for (size_t i = 0; i < pObjSprite->size_.Y; i++)
			{
				if (mapInfo->vMapInfo[objPosition.X - 1][objPosition.Y + i].belongWho !=whitchActor)
				{
					canDraw = true;
					break;
				}
			}
			objPosition.X--;
			for (size_t i = 0; i < pObjSprite->size_.Y; i++)
			{
				mapInfo->vMapInfo[objPosition.X][objPosition.Y + i].isBlock = true;
				mapInfo->vMapInfo[objPosition.X + pObjSprite->size_.X][objPosition.Y + i].isBlock = false;
			}
			if (canDraw)
			{
				inkPower -= 1;
				if (inkPower<0)
				{
					inkPower = 0;
				}
				else
				{
					for (size_t i = 0; i < pObjSprite->size_.Y; i++)
					{
						mapInfo->vMapInfo[objPosition.X][objPosition.Y + i].belongWho = whitchActor;
					}
				}
			}
		}
	}
}

void GameActor::right()
{
	std::string spname = { "player" };
	spname = spname + std::to_string(whitchActor) + "right";
	pObjSprite = uomSprites->find(spname)->second;
	if (objPosition.X + pObjSprite->size_.X < sceneInfo->getScreenSize().X)
	{
		//if can move
		bool canMove = true;
		bool canDraw = false;
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
			for (size_t i = 0; i < pObjSprite->size_.Y; i++)
			{
				if (mapInfo->vMapInfo[objPosition.X + pObjSprite->size_.X][objPosition.Y + i].belongWho != whitchActor)
				{
					canDraw = true;
					break;
				}
			}
			objPosition.X++;
			for (size_t i = 0; i < pObjSprite->size_.Y; i++)
			{
				mapInfo->vMapInfo[objPosition.X - 1][objPosition.Y + i].isBlock = false;
				mapInfo->vMapInfo[objPosition.X + pObjSprite->size_.X - 1][objPosition.Y + i].isBlock = true;
			}
			if (canDraw)
			{
				inkPower -= 1;
				if (inkPower<0)
				{
					inkPower = 0;
				}
				else
				{
					for (size_t i = 0; i < pObjSprite->size_.Y; i++)
					{
						mapInfo->vMapInfo[objPosition.X + pObjSprite->size_.X - 1][objPosition.Y + i].belongWho = whitchActor;
					}
				}
			}
		}
	}
}

