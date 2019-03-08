/*
author:zhang ruisong
date:2019.3.9
GameActor inherit from GameObject
*/
#pragma once
#include<string>
#include "GameObject.h"


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

	//different actor  has actions itseft
	int whitchActor;

private:
	CHAR_INFO* actorColor;
	bool isMoved = false;
	int inkPower = 12;
	//to remeber actor numbers(how many)
	static int actorNum;
	std::unordered_map<std::string, CHAR_INFO*>* colorRes;

};