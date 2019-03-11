#include "GameObject.h"

GameObject::GameObject(COORD pos_, const std::string& name_, 
	std::unordered_map<std::string, Sprite*>& msp_,
	Scene& sceneInfo_,MapInformation& mapInfo_)
	:objPosition(pos_),objOldPosition(pos_),
	objName(name_), uomSprites(&msp_),sceneInfo(&sceneInfo_),
	mapInfo(&mapInfo_)
{
	
	pObjSprite = loadSpriteByName(objName);
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	writeToScreenInfo();
}

Sprite GameObject::loadSpriteByName(const std::string key)
{
	return *(uomSprites->find(key)->second);
}

void GameObject::writeToScreenInfo()
{
	for (size_t i = 0; i < pObjSprite.size_.X; i++)
	{
		for (size_t j = 0; j < pObjSprite.size_.Y; j++)
		{
			if (pObjSprite.isBlank_[j * pObjSprite.size_.X + i] == true)
			{
				sceneInfo->getSceneInfo()[(j + objPosition.Y)*  sceneInfo->getScreenSize().X + i + objPosition.X] = pObjSprite.charInfo_[j * pObjSprite.size_.X + i];
			}
		}
	}
}
