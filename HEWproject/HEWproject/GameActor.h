#pragma once
#include<string>
#include "GameObject.h"

class GameActor :
	public GameObject
{
public:
	GameActor(COORD, Sprite&, const std::string&);
	~GameActor();

	//update gameobject state
	virtual void update(Scene* screenInf);

	//gameobject control functions
	void up();
	void down();
	void left();
	void right();

	int whitchActor;
private:
	int velocity_;

	//to remeber actor numbers(how many)
	static int actorNum;
};