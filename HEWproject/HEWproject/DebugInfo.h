#pragma once
#include<Windows.h>
#include<vector>
#include<sstream>
#include"Scene.h"


class DebugInfo
{
public:
	DebugInfo(Scene&);
	~DebugInfo();

	void writeDebugInfo(const int timeFromlast);

	//void writeDebugInfoToScene();

private:
	Scene * sceneDebug;
};

