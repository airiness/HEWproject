/*
author:zhang ruisong
date:2019.3.7
class debugInformation
*/
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

	//write info to buffer
	void writeDebugInfo(const int timeFromlast);
private:
	Scene * sceneDebug;
};

