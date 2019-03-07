#pragma once
#include<string>
#include "GameObject.h"

class GameActor :
	public GameObject
{
public:
	GameActor(COORD, Sprite&, const std::string&);
	~GameActor();
	
	//handle the inputs
	virtual void inputHandleObj(InputHandler & inputHandler);
	//update gameobject state
	virtual void update(Scene* screenInf);

	//gameobject control functions
	virtual void up();
	virtual void down();
	virtual void left();
	virtual void right();


private:
	int velocity_;
	int whitchActor;
	//to remeber actor numbers(how many)
	static int actorNum;
};