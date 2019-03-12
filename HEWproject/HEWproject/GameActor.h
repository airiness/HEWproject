/*
author:zhang ruisong
date:2019.3.9
GameActor inherit from GameObject
*/
#pragma once
#include<string>
#include"GameObject.h"
#include"Bullet.h"

constexpr auto INK_POWER = 48;
constexpr auto ACTOR_SPEED = 1;
constexpr auto step = 8;

class GameActor :
	public GameObject
{
public:
	GameActor(COORD, const std::string&, 
		std::unordered_map<std::string, Sprite*>&,
		Scene&,MapInformation&,
		std::unordered_map<std::string, CHAR_INFO*>&);
	~GameActor();


	//real update
	void update(const GameActor & actor);

	//update gameobject state
	virtual void update();

	//gameobject control functions
	void up();
	void down();
	void left();
	void right();
	void shoot();
	void plusPower();

	//different actor  has actions itseft
	int whitchActor;

private:
	inline void updateState(const GameActor & actor)
	{
		if (objPosition.X < (actor.pbullet->objPosition.X + actor.pbullet->objSprite.size_.X )&&
			(objPosition.X + objSprite.size_.X) > actor.pbullet->objPosition.X &&
			objPosition.Y < (actor.pbullet->objPosition.Y + actor.pbullet->objSprite.size_.Y) &&
			(objPosition.Y + objSprite.size_.Y) > actor.pbullet->objPosition.Y &&
			actor.pbullet->isUse == true)
		{
			actor.pbullet->isUse = false;
			inkPower = 0;
		}

		std::string colorName = { "player" };
		colorName = colorName + std::to_string(whitchActor) + "power";
		CHAR_INFO * colorPower = colorRes->find(colorName)->second;
		CHAR_INFO * lowPower = colorRes->find("playernopower")->second;

		//ican't find a  good way
		//but now this is fucking stupid code
		auto tFlag = (inkPower + 1)/ step;
		if (tFlag > 0)
		{
			for (size_t i = 2; i < 14; i++)
			{
				objSprite.charInfo_[6 * objSprite.size_.X + i] = *colorPower;
			}
			tFlag--;
		}
		else
		{
			for (size_t i = 2; i < 14; i++)
			{
				objSprite.charInfo_[6 * objSprite.size_.X + i] = *lowPower;
			}
		}
		if (tFlag > 0)
		{
			for (size_t i = 2; i < 6; i++)
			{
				objSprite.charInfo_[5 * objSprite.size_.X + i] = *colorPower;
				objSprite.charInfo_[5 * objSprite.size_.X + i + 8] = *colorPower;
			}
			tFlag--;
		}
		else
		{
			for (size_t i = 2; i < 6; i++)
			{
				objSprite.charInfo_[5 * objSprite.size_.X + i] = *lowPower;
				objSprite.charInfo_[5 * objSprite.size_.X + i + 8] = *lowPower;
			}
		}
		if (tFlag > 0)
		{
			for (size_t i = 2; i < 14; i++)
			{
				objSprite.charInfo_[4 * objSprite.size_.X + i] = *colorPower;
			}
			tFlag--;
		}
		else
		{
			for (size_t i = 2; i < 14; i++)
			{
				objSprite.charInfo_[4 * objSprite.size_.X + i] = *lowPower;
			}
		}
		if (tFlag > 0)
		{
			objSprite.charInfo_[3 * objSprite.size_.X + 2] = *colorPower;
			objSprite.charInfo_[3 * objSprite.size_.X + 7] = *colorPower;
			if (objSprite.spriteName_.substr(objSprite.spriteName_.size()-4, objSprite.spriteName_.size()) == "left")
			{
				objSprite.charInfo_[3 * objSprite.size_.X + 5] = *colorPower;
				objSprite.charInfo_[3 * objSprite.size_.X + 6] = *colorPower;
				objSprite.charInfo_[3 * objSprite.size_.X + 11] = *colorPower;
				objSprite.charInfo_[3 * objSprite.size_.X + 12] = *colorPower;
			}
			else
			{
				objSprite.charInfo_[3 * objSprite.size_.X + 3] = *colorPower;
				objSprite.charInfo_[3 * objSprite.size_.X + 4] = *colorPower;
				objSprite.charInfo_[3 * objSprite.size_.X + 9] = *colorPower;
				objSprite.charInfo_[3 * objSprite.size_.X + 10] = *colorPower;
			}
			objSprite.charInfo_[3 * objSprite.size_.X + 8] = *colorPower;
			objSprite.charInfo_[3 * objSprite.size_.X + 13] = *colorPower;
			tFlag--;			
		}						
		else					
		{						
			objSprite.charInfo_[3 * objSprite.size_.X + 2] = *lowPower;
			objSprite.charInfo_[3 * objSprite.size_.X + 7] = *lowPower;
			if (objSprite.spriteName_.substr(objSprite.spriteName_.size() - 4, objSprite.spriteName_.size()) == "left")
			{
				objSprite.charInfo_[3 * objSprite.size_.X + 5] = *lowPower;
				objSprite.charInfo_[3 * objSprite.size_.X + 6] = *lowPower;
				objSprite.charInfo_[3 * objSprite.size_.X + 11] = *lowPower;
				objSprite.charInfo_[3 * objSprite.size_.X + 12] = *lowPower;
			}
			else
			{
				objSprite.charInfo_[3 * objSprite.size_.X + 3] = *lowPower;
				objSprite.charInfo_[3 * objSprite.size_.X + 4] = *lowPower;
				objSprite.charInfo_[3 * objSprite.size_.X + 9] = *lowPower;
				objSprite.charInfo_[3 * objSprite.size_.X + 10] = *lowPower;
			}
			objSprite.charInfo_[3 * objSprite.size_.X + 8] = *lowPower;
			objSprite.charInfo_[3 * objSprite.size_.X + 13] = *lowPower;
		}
		if (tFlag > 0)
		{
			objSprite.charInfo_[2 * objSprite.size_.X + 2] = *colorPower;
			objSprite.charInfo_[2 * objSprite.size_.X + 7] = *colorPower;
			objSprite.charInfo_[2 * objSprite.size_.X + 8] = *colorPower;
			objSprite.charInfo_[2 * objSprite.size_.X + 13] = *colorPower;
			tFlag--;			
		}						
		else					
		{						
			objSprite.charInfo_[2 * objSprite.size_.X + 2] = *lowPower;
			objSprite.charInfo_[2 * objSprite.size_.X + 7] = *lowPower;
			objSprite.charInfo_[2 * objSprite.size_.X + 8] = *lowPower;
			objSprite.charInfo_[2 * objSprite.size_.X + 13] = *lowPower;
		}
		if (tFlag > 0)
		{
			for (size_t i = 2; i < 14; i++)
			{
				objSprite.charInfo_[1 * objSprite.size_.X + i] = *colorPower;
			}
		}
		else
		{
			for (size_t i = 2; i < 14; i++)
			{
				objSprite.charInfo_[1 * objSprite.size_.X + i] = *lowPower;
			}
		}


		//show score need too much cpu.fuck it!
		/*
		update score
		score = 0;
		for (auto & r : mapInfo->vMapInfo)
		{
			for (auto & c : r)
			{
				if (whitchActor == c.belongWho)
				{
					score++;
				}
			}
		}
		int tmpscore = score;
		show score
		int scorePos = objSprite.size_.X * objSprite.size_.Y;
		while (tmpscore!=0)
		{
			objSprite.charInfo_[--scorePos].Char.UnicodeChar = 48+tmpscore % 10;
			//objSprite.charInfo_[scorePos].Attributes += 0x09;
			tmpscore /= 10;
		}
		*/
	}

	Bullet * pbullet;

	CHAR_INFO* actorColor;	//facecolor of actor		
	int inkPower = INK_POWER;	//	
	int speed = ACTOR_SPEED;
	int pressedTime;
	int timeLastPress;
	bool timeLastPressInit;
	//to remeber actor numbers(how many)
	static int actorNum;
	std::unordered_map<std::string, CHAR_INFO*>* colorRes;

};