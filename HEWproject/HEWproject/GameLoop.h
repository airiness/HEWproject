/*
author:zhang ruisong
date:2019.3.7
game main loop class
*/
#pragma once
#include<Windows.h>
#include<vector>
#include<unordered_map>
#include<fstream>
#include"DebugInfo.h"
#include"InputHandler.h"
#include"MapInformation.h"
#include"Scene.h"
#include"GameActor.h"
using namespace std;

//screen size
constexpr auto SCENE_WIDTH = 160;
constexpr auto SCENE_HEIGHT = 40;

//gamestate different state do different things
enum GameState
{
	TITLE,
	INGAME,
	RESULT
};

class GameLoop
{
private:
	// init sub functions
	inline void inithandleBuffers()
	{
		//create two handles for double buffer
		//buffer handle1
		std_h = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			CONSOLE_TEXTMODE_BUFFER,
			NULL
		);
		//GetStdHandle(STD_OUTPUT_HANDLE);
		//buffer handle2
		buffer_h = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			CONSOLE_TEXTMODE_BUFFER,
			NULL
		);
		//make cursor unvisible
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 1;
		info.bVisible = FALSE;
		SetConsoleCursorInfo(std_h, &info);
		SetConsoleCursorInfo(buffer_h, &info);
		//set console window name 
		SetConsoleTitle(L"HEWプロジェクト");
	}
	inline void initGameCompanent()
	{
		//init the scene
		COORD screenSize{ SCENE_WIDTH ,SCENE_HEIGHT };//--screen size
		mainScene = new Scene(std_h, buffer_h, pixelsOfScene, screenSize);
		//init mapInformation,for collition
		mainMapInfo = new MapInformation(screenSize);
		//init input handler
		inputHandler = new InputHandler();
	}
	inline void initGameResource()
	{
		//load sprites
		fstream fsprites("SpriteList");
		if (!fsprites)
		{
			return;
		}
		while (!fsprites.eof())
		{
			string spriteName;
			fsprites >> spriteName;
			spRes.insert(pair<string, Sprite*>(spriteName, new Sprite(spriteName)));
		}
		//create actors items and save them
		COORD player1coord = { 5,5 };
		COORD player2coord = { 100,20 };
		CHAR_INFO player1color;
		player1color.Attributes = 0xAB;
		player1color.Char.UnicodeChar = 0x2665;
		CHAR_INFO player2color;
		player2color.Attributes = 0xCD;
		actors.push_back(new GameActor(player1coord, "player1right", spRes, *mainScene, *mainMapInfo, player1color));
		actors.push_back(new GameActor(player2coord, "player2left", spRes, *mainScene, *mainMapInfo, player2color));
		for (auto & a : actors)
		{
			pObjects.push_back(a);
		}
	}

private:
	///------
	HANDLE std_h, buffer_h;									//two handles for double buffer
	GameState gameState = INGAME;							//control game state
	CHAR_INFO pixelsOfScene[SCENE_WIDTH * SCENE_HEIGHT];	//screen buffer infor
	vector<GameObject*> pObjects;							//save game actor
	vector<GameActor*> actors;								//save gameactor's pointer
	unordered_map<string, Sprite*> spRes;					//save sprites
	Scene * mainScene;										//sreenscene
	InputHandler * inputHandler;							//inputhandler
	MapInformation * mainMapInfo;								//mapinformation

public:
	GameLoop();
	~GameLoop();
	//game loop
	void gloop();

private:
	//initial function
	void init();
	//unintial
	void uninit();
	//update all game objects
	void update();
	//deal the inputs of actors
	void handleInput(vector<GameActor*>&);
};

