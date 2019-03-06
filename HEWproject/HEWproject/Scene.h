#pragma once
#include<Windows.h>
#include<string>

class Scene
{
public:
	Scene();
	Scene(HANDLE& , HANDLE& , CHAR_INFO*,COORD);
	~Scene();

	//draw the screen
	void draw();
	void setPos(COORD);
	void writeStr(char*);
	void writeStr(const std::string&);

	//swap the  buffer
	void swap();

	//
	//CHAR_INFO* getSceneInfo();

private:
	HANDLE * current_;	//
	HANDLE * next_;
	COORD sceneSize;
	COORD sceneCoord;
	SMALL_RECT srctReadRect;
	CHAR_INFO * pixels;
};

