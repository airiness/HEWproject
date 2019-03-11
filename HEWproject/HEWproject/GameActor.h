/*
author:zhang ruisong
date:2019.3.9
GameActor inherit from GameObject
*/
#pragma once
#include<string>
#include "GameObject.h"

#define INK_POWER 12
#define ACTOR_SPEED 1

//actor state 
enum ActorState
{
	ATTACK,
	MOVE
};

class GameActor :
	public GameObject
{
public:
	GameActor(COORD, const std::string&, 
		std::unordered_map<std::string, Sprite*>&,
		Scene&,MapInformation&,
		std::unordered_map<std::string, CHAR_INFO*>&);
	~GameActor();

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
	inline void updateState()
	{
		//show score need too much cpu.fuck it!
		//update score
		//score = 0;
		//for (auto & r : mapInfo->vMapInfo)
		//{
		//	for (auto & c : r)
		//	{
		//		if (whitchActor == c.belongWho)
		//		{
		//			score++;
		//		}
		//	}
		//}
		//int tmpscore = score;


		//show score
		//int scorePos = pObjSprite.size_.X * pObjSprite.size_.Y;
		//while (tmpscore!=0)
		//{
		//	pObjSprite.charInfo_[--scorePos].Char.UnicodeChar = 48+tmpscore % 10;
		//	//pObjSprite.charInfo_[scorePos].Attributes += 0x09;
		//	tmpscore /= 10;
		//}


	}


	CHAR_INFO* actorColor;
	int score = 0;
	bool isMoved = false;
	int inkPower = INK_POWER;
	int speed = ACTOR_SPEED;
	//to remeber actor numbers(how many)
	static int actorNum;
	std::unordered_map<std::string, CHAR_INFO*>* colorRes;
};