#pragma once
#include<string>
#include "GameObject.h"
class GameActor :
	public GameObject
{
public:
	GameActor(COORD, Sprite&, const std::string&);
	~GameActor();

	virtual void update(Scene* screenInf);

	virtual void jump();
	virtual void left();
	virtual void right();
private:
	int velocity_;
};