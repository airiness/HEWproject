#include "GameObject.h"

GameObject::GameObject()
:objPosition{0,0},pObjSprite(nullptr)
{
	 
}

GameObject::GameObject(COORD  pos_,Sprite & sp_,const std::string& name_)
	:objPosition(pos_),pObjSprite(&sp_),objName(name_)
{

}

GameObject::~GameObject()
{
}

void GameObject::update(Scene* screenInfo)
{
	writeToScreenInfo(screenInfo);
}

void GameObject::writeToScreenInfo(Scene * screenInfo)
{
	for (size_t i = 0; i < pObjSprite->size_.X; i++)
	{
		for (size_t j = 0; j < pObjSprite->size_.Y; j++)
		{
			if (pObjSprite->isBlank_[j * pObjSprite->size_.X + i] == true)
			{
				screenInfo->getSceneInfo()[(j + objPosition.Y)*  screenInfo->getScreenSize().X + i + objPosition.X] = pObjSprite->charInfo_[j * pObjSprite->size_.X + i];
			}
		}
	}
}
