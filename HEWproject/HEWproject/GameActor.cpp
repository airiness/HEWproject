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
	//begin position can not move to
	//set begin position area to each other
	for (size_t i = 0; i < objSprite.size_.X; i++)
	{
		for (size_t j = 0; j < objSprite.size_.Y; j++)
		{
			mapInfo->vMapInfo[position_.X + i][position_.Y + j].isBlock = whitchActor;
			mapInfo->vMapInfo[position_.X + i][position_.Y + j].belongWho = whitchActor;
		}
	}

	std::string colorName = { "player" };
	colorName = colorName + std::to_string(whitchActor) + "color";
	actorColor = colorRes->find(colorName)->second;
	pressedTime = 0;
	timeLastPress = GetTickCount();
	timeLastPressInit = false;
	//init bullet
	pbullet = new Bullet({ 0,0 }, "Bullet", msp_, sceneInfo_, mapInfo_, whitchActor);
	if (objSprite.spriteName_.substr(objSprite.spriteName_.size() - 4, objSprite.spriteName_.size()) == "left")
	{
		pbullet->isLeft = true;
	}
	else
	{
		pbullet->isLeft = false;
	}
}

GameActor::~GameActor()
{
	actorNum--;
	delete pbullet;

}


void GameActor::update(const GameActor& actor)
{
	updateState(actor);
	for (size_t i = 0; i < objSprite.size_.X; i++)
	{
		for (size_t j = 0; j < objSprite.size_.Y; j++)
		{
			sceneInfo->getSceneInfo()[(j + objPosition.Y)*  sceneInfo->getScreenSize().X + i + objPosition.X]
				= objSprite.charInfo_[j * objSprite.size_.X + i];
		}
	}
	pbullet->update();
}

void GameActor::update()
{
}

//when actor move up
//ditective if can move or not
//if have ink draw 
void GameActor::up()
{
	pressedTime = 0;
	timeLastPressInit = false;
	if (objPosition.Y > 0)
	{
		bool canMove = true;
		bool canDraw = false;
		for (size_t i = 0; i < objSprite.size_.X; i++)
		{
			if (mapInfo->vMapInfo[objPosition.X + i][objPosition.Y - 1].isBlock)
			{
				canMove = false;
				break;
			}
		}
		if (canMove)
		{
			for (size_t i = 0; i < objSprite.size_.X; i++)
			{
				if (mapInfo->vMapInfo[objPosition.X +i][objPosition.Y -1].belongWho != whitchActor)
				{
					canDraw = true;
					break;
				}
			}
			objPosition.Y--;
			for (size_t i = 0; i < objSprite.size_.X; i++)
			{
				mapInfo->vMapInfo[objPosition.X + i][objPosition.Y].isBlock = whitchActor;
				mapInfo->vMapInfo[objPosition.X + i][objPosition.Y + objSprite.size_.Y].isBlock = 0;
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
					for (size_t i = 0; i < objSprite.size_.X; i++)
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
	pressedTime = 0;
	timeLastPressInit = false;
	if (objPosition.Y + objSprite.size_.Y < sceneInfo->getScreenSize().Y)
	{
		bool canMove = true;
		bool canDraw = false;
		for (size_t i = 0; i < objSprite.size_.X; i++)
		{
			if (mapInfo->vMapInfo[objPosition.X + i][objPosition.Y + objSprite.size_.Y].isBlock)
			{
				canMove = false;
				break;
			}
		}
		if (canMove)
		{
			for (size_t i = 0; i < objSprite.size_.X; i++)
			{
				if (mapInfo->vMapInfo[objPosition.X + i][objPosition.Y + objSprite.size_.Y].belongWho != whitchActor)
				{
					canDraw = true;
					break;
				}
			}
			objPosition.Y++;
			for (size_t i = 0; i < objSprite.size_.X; i++)
			{
				mapInfo->vMapInfo[objPosition.X + i][objPosition.Y - 1].isBlock = 0;
				mapInfo->vMapInfo[objPosition.X + i][objPosition.Y + objSprite.size_.Y - 1].isBlock = whitchActor;
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
					for (size_t i = 0; i < objSprite.size_.X; i++)
					{
						mapInfo->vMapInfo[objPosition.X + i][objPosition.Y + objSprite.size_.Y - 1].belongWho = whitchActor;
					}
				}
			}
		}
	}
}
//when actor move to left
void GameActor::left()
{

	pressedTime = 0;
	timeLastPressInit = false;
	//change bullet direction
	pbullet->isLeft = true;
	//when change direction,change sprite
	std::string spname = { "player" };
	spname = spname + std::to_string(whitchActor) + "left";
	objSprite = *uomSprites->find(spname)->second;
	//if actor in the scene
	if (objPosition.X > 0)
	{
		//if the actor collicted by other actors
		bool canMove = true;
		//have power to draw ?
		bool canDraw = false;
		//collition
		for (size_t i = 0; i < objSprite.size_.Y; i++)
		{
			if (mapInfo->vMapInfo[objPosition.X - 1][objPosition.Y + i].isBlock)
			{
				canMove = false;
				break;
			}
		}
		if (canMove)
		{
			for (size_t i = 0; i < objSprite.size_.Y; i++)
			{
				if (mapInfo->vMapInfo[objPosition.X - 1][objPosition.Y + i].belongWho !=whitchActor)
				{
					canDraw = true;
					break;
				}
			}
			objPosition.X--;
			for (size_t i = 0; i < objSprite.size_.Y; i++)
			{
				mapInfo->vMapInfo[objPosition.X][objPosition.Y + i].isBlock = whitchActor;
				mapInfo->vMapInfo[objPosition.X + objSprite.size_.X][objPosition.Y + i].isBlock = 0;
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
					for (size_t i = 0; i < objSprite.size_.Y; i++)
					{
						mapInfo->vMapInfo[objPosition.X][objPosition.Y + i].belongWho = whitchActor;
					}
				}
			}
		}
	}
}
//when actor move to right 
void GameActor::right()
{
	pressedTime = 0;
	timeLastPressInit = false;
	pbullet->isLeft = false;
	std::string spname = { "player" };
	spname = spname + std::to_string(whitchActor) + "right";
	objSprite = *uomSprites->find(spname)->second;
	if (objPosition.X + objSprite.size_.X < sceneInfo->getScreenSize().X)
	{
		//if can move
		bool canMove = true;
		bool canDraw = false;
		for (size_t i = 0; i < objSprite.size_.Y; i++)
		{
			if (mapInfo->vMapInfo[objPosition.X + objSprite.size_.X][objPosition.Y + i].isBlock)
			{
				canMove = false;
				break;
			}
		}
		if (canMove)
		{
			for (size_t i = 0; i < objSprite.size_.Y; i++)
			{
				if (mapInfo->vMapInfo[objPosition.X + objSprite.size_.X][objPosition.Y + i].belongWho != whitchActor)
				{
					canDraw = true;
					break;
				}
			}
			objPosition.X++;
			for (size_t i = 0; i < objSprite.size_.Y; i++)
			{
				mapInfo->vMapInfo[objPosition.X - 1][objPosition.Y + i].isBlock = 0;
				mapInfo->vMapInfo[objPosition.X + objSprite.size_.X - 1][objPosition.Y + i].isBlock = whitchActor;
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
					for (size_t i = 0; i < objSprite.size_.Y; i++)
					{
						mapInfo->vMapInfo[objPosition.X + objSprite.size_.X - 1][objPosition.Y + i].belongWho = whitchActor;
					}
				}
			}
		}
	}
}

void GameActor::shoot()
{
	pressedTime = 0;
	timeLastPressInit = false;
	if (pbullet->isUse == false && inkPower > 0)
	{
		pbullet->isUse = true;
		pbullet->setBulletPos({objPosition.X, objPosition.Y + 2	});
		pbullet->bulletSpeed =( pbullet->isLeft ? -2 : 2);
		inkPower -= (step / 2);
	}

}

//plus inkpower
void GameActor::plusPower()
{
	if (timeLastPressInit == false)
	{
		timeLastPress = GetTickCount();
		timeLastPressInit = true;
	}
	auto now = GetTickCount();
	pressedTime = now - timeLastPress;
	
	bool isOnField = false;

	for (size_t i = 0; i < objSprite.size_.X; i++)
	{
		for (size_t j = 0; j < objSprite.size_.Y; j++)
		{
			if (mapInfo->vMapInfo[objPosition.X + i][objPosition.Y + j].belongWho == whitchActor)
			{
				isOnField = true;
				break;
			}

		}
		if (isOnField == true)
		{
			break;
		}
	}
	if ( isOnField == true && inkPower < INK_POWER && pressedTime>50)
	{
		inkPower++;
		pressedTime = 0;
		timeLastPress = GetTickCount();
	}
}

