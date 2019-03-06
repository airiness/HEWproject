#include "GameObject.h"

GameObject::GameObject()
:objPosition{0,0},pObjectSprite(nullptr)
{
	 
}

GameObject::GameObject(COORD & pos_,Sprite & sp_)
	:objPosition(pos_),pObjectSprite(&sp_)
{
}


GameObject::~GameObject()
{
}

void GameObject::update()
{

}
