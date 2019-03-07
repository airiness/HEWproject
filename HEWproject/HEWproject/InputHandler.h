/*
author:zhang ruisong
date:2019.3.7
class handle input
*/
#pragma once
#include<Windows.h>
#include<memory>
#include"Command.h"
#pragma comment(lib, "winmm.lib")

#define PM_CURX					0x0101
#define PM_CURY					0x0102

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	Command* handleInput();

	void initCommand();
	void uninitCommand();
	//this code is come from conioex
	//handle the keyboard mouse joycon input
	int inputSth(int);

private:
	DWORD dwKeyMap[8];
	COORD crdMouse;
	Command * buttonA_;
	Command * buttonD_;
	Command * buttonSpace_;
};

