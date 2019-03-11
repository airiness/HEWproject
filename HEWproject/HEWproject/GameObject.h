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
#include"MapInformation.h"
#include"Sprite.h"
class GameObject
{
public:
	GameObject(COORD,const std::string&, std::unordered_map<std::string, Sprite*>&, Scene&,MapInformation&);
	virtual ~GameObject();
	//update the object state
	virtual void update();

	std::string objName;//object name
	COORD objOldPosition;	//old position
	COORD objPosition; // object position
	Sprite pObjSprite; //the sprite of object
	bool isUse; //is the object useful
	bool isEntity = false; // phsical
protected:
	std::unordered_map<std::string, Sprite*> * uomSprites;
	Scene * sceneInfo;			//mainscene
	MapInformation* mapInfo;	//mapinfo for collition
	//load sprite
	Sprite loadSpriteByName(const std::string);


private:
	//get sprite to show
	void writeToScreenInfo();
};

