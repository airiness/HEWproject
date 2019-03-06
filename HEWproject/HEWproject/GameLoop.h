#pragma once
#include<Windows.h>
#include<vector>
#include"DebugInfo.h"
#include"Scene.h"
#include"Charactor.h"
using namespace std;

constexpr auto SCENE_WIDTH = 130;
constexpr auto SCENE_HEIGHT = 30;

//#define SCENE_WIDTH 130
//#define SCENE_HEIGHT 30

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
	void init();
	void uninit();
	void update();


	HANDLE std_h, buffer_h;	//two handles for double buffer
	GameState gameState = TITLE;	//control game state
	CHAR_INFO pixelsOfScene[SCENE_WIDTH * SCENE_HEIGHT]; //screen buffer infor
	//screenScene
	std::vector<GameObject*> objects;

	Scene * mainScene;
};

