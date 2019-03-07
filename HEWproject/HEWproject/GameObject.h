#pragma once
#include<Windows.h>
#include"Scene.h"
#include"Sprite.h"
class GameObject
{
public:
	GameObject();
	GameObject(COORD, Sprite &,const std::string&);
	virtual ~GameObject();

	virtual void update(Scene* screenInfo);

	//object name
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

