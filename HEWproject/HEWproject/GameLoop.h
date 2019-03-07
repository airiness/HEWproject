/*
author:zhang ruisong
date:2019.3.7
game main loop class
*/
#pragma once
#include<Windows.h>
#include<vector>
#include<map>
#include"DebugInfo.h"
#include"InputHandler.h"
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
public:
	GameLoop();
	~GameLoop();
	
	void gloop();

private:
	//initial function
	void init();
	//unintial
	void uninit();

	void update();
	void handleInput(std::vector<GameActor*>&);

	Sprite* getSprite(const std::string&);
	HANDLE std_h, buffer_h;	//two handles for double buffer
	GameState gameState = INGAME;	//control game state
	CHAR_INFO pixelsOfScene[SCENE_WIDTH * SCENE_HEIGHT]; //screen buffer infor
	std::vector<GameObject*> pObjects;	//save game actor
	std::vector<GameActor*> actors;
	std::map<std::string, Sprite*> spRes;	// save sprites
	Scene * mainScene;	//sreenscene
	InputHandler * inputHandler;	//inputhandler
};

