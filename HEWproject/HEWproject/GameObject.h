/*
author:zhang ruisong
date:2019.3.9
basoc game object
*/
#pragma once
#include<Windows.h>
#include<unordered_map>
#include<string>
#include"Scene.h"
#include"Sprite.h"
class GameObject
{
public:
	GameObject(COORD,const std::string&, std::unordered_map<std::string, Sprite*>&);
	virtual ~GameObject();
	//update the object state
	virtual void update(Scene* screenInfo);
	
	std::string objName;//object name
	COORD objPosition; // object position
	Sprite *pObjSprite; //the sprite of object
	bool isUse; //is the object useful

private:
	std::unordered_map<std::string, Sprite*> * uomSprites;
	Sprite* loadSpriteByName(const std::string);

	void writeToScreenInfo(Scene* screenInfo);
};

