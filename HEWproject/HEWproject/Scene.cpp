#include "Scene.h"


Scene::Scene()
	:current_(nullptr), next_(nullptr), pixels(nullptr),
	sceneSize({0,0}), sceneCoord({ 0,0 }),
	srctReadRect({ 0,0,0,0 })
{
}

Scene::Scene(HANDLE & buffer1_,HANDLE & buffer2_,CHAR_INFO * pixils_,COORD sceneSize)
	:current_(&buffer1_),next_(&buffer2_), pixels(pixils_),
	sceneSize(sceneSize),sceneCoord({0,0}),
	srctReadRect({0,0,sceneSize.X,sceneSize.Y })
{
	
}

Scene::~Scene()
{

}

void Scene::draw()
{
	WriteConsoleOutput(*next_, pixels, sceneSize, sceneCoord, &srctReadRect);

}

void Scene::setPos(COORD pos)
{
	SetConsoleCursorPosition(*next_, pos);
}

void Scene::writeStr(char *ch)
{
	DWORD len = strlen(ch);
	WriteConsoleA(*next_, ch, len, &len, 0);
}

void Scene::writeStr(const std::string& str)
{
	DWORD len = str.size();
	WriteConsoleA(*next_, str.c_str(), len, &len, 0);
}

//swap the buffer 
void Scene::swap()
{
	HANDLE * tmp = current_;
	current_ = next_;
	next_ = tmp;
	SetConsoleActiveScreenBuffer(*current_);
}


//CHAR_INFO* Scene::getSceneInfo()
//{
//	return pixels;
//}


