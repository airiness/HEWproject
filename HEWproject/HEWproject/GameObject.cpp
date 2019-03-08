#include "GameObject.h"

GameObject::GameObject(COORD  pos_, const std::string& name_, std::unordered_map<std::string, Sprite*>& msp_)
	:objPosition(pos_), pObjSprite(nullptr), objName(name_), uomSprites(&msp_)
{
	pObjSprite = loadSpriteByName(objName);
}

GameObject::~GameObject()
{
}

void GameObject::update(Scene* screenInfo)
{
	writeToScreenInfo(screenInfo);
}

Sprite * GameObject::loadSpriteByName(const std::string key)
{
	return uomSprites->find(key)->second;
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
