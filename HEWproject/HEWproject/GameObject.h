#pragma once
#include<Windows.h>
#include"Sprite.h"
class GameObject
{
public:
	GameObject();
	GameObject(COORD &, Sprite &);
	virtual ~GameObject();
	virtual void update();

private:
	COORD objPosition;
	Sprite *pObjectSprite;
};

