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
constexpr auto SCENE_WIDTH = 120;
constexpr auto SCENE_HEIGHT = 40;
constexpr auto GAME_TIME = 6000;	//game time 

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
		mainMapInfo = new MapInformation(screenSize,*mainScene,colorRes);
		//init input handler
		inputHandler = new InputHandler();
		gameTimeNow = GetTickCount();
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
		COORD player2coord = { 60,20 };

		colorRes.insert(pair<string, CHAR_INFO*>("player1color", new CHAR_INFO{ 0x2665 ,0xAB }));
		colorRes.insert(pair<string, CHAR_INFO*>("player2color", new CHAR_INFO{ 0x2661, 0xCD }));
		colorRes.insert(pair<string, CHAR_INFO*>("player1power", new CHAR_INFO{ ' ', 0xAB }));
		colorRes.insert(pair<string, CHAR_INFO*>("player2power", new CHAR_INFO{ ' ', 0xCD }));
		colorRes.insert(pair<string, CHAR_INFO*>("playernopower", new CHAR_INFO{ ' ', 0xFF }));

		actors.push_back(new GameActor(player1coord, "player1right", spRes, *mainScene, *mainMapInfo, colorRes));
		actors.push_back(new GameActor(player2coord, "player2left", spRes, *mainScene, *mainMapInfo, colorRes));
		for (auto & a : actors)
		{
			pObjects.push_back(a);
		}

		objTitleAndResult = new GameObject({ 0,0 }, "Title", spRes, *mainScene, *mainMapInfo);
		//objResult = new GameObject({ 0,0 }, "Result", spRes, *mainScene, *mainMapInfo);
	}

private:
	///------
	HANDLE std_h, buffer_h;									//two handles for double buffer
	GameState gameState = TITLE;							//control game state
	CHAR_INFO pixelsOfScene[SCENE_WIDTH * SCENE_HEIGHT];	//screen buffer infor
	vector<GameObject*> pObjects;							//save game actor
	vector<GameActor*> actors;								//save gameactor's pointer
	unordered_map<string, Sprite*> spRes;					//save sprites
	unordered_map<string, CHAR_INFO*> colorRes;				//color resource
	Scene * mainScene;										//sreenscene
	InputHandler * inputHandler;							//inputhandler
	MapInformation * mainMapInfo;							//mapinformation

	GameObject * objTitleAndResult;

	int gameTime = GAME_TIME;
	int gameTimeNow = 0;
	bool gameTimeInited = false;
	int player1Point = 0;
	int player2Point = 0;
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
	//when the game begin next time,re all the resource and compnent
	void reAllComponent();
	//deal the inputs of actors
	void handleInput(vector<GameActor*>&);
};

