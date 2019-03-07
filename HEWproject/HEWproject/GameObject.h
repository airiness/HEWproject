#pragma once
#include<Windows.h>
#include"InputHandler.h"
#include"Scene.h"
#include"Sprite.h"
class GameObject
{
public:
	GameObject();
	GameObject(COORD, Sprite &,const std::string&);
	virtual ~GameObject();

	virtual void inputHandleObj(InputHandler & inputHandler);
	virtual void update(Scene* screenInfo);

	virtual void up();
	virtual void down();
	virtual void left();
	virtual void right();


	//
	std::string objName;
	// object position
	COORD objPosition;
	//the sprite of object
	Sprite *pObjSprite;
	//is the object useful
	bool isUse;

private:
	void writeToScreenInfo(Scene* screenInfo);
};

