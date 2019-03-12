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
	COORD objPosition; // object position
	Sprite objSprite; //the sprite of object
	Sprite loadSpriteByName(const std::string);
protected:
	std::unordered_map<std::string, Sprite*> * uomSprites;
	Scene * sceneInfo;			//mainscene
	MapInformation* mapInfo;	//mapinfo for collition
	//load sprite


private:
	//get sprite to show
	void writeToScreenInfo();
};

