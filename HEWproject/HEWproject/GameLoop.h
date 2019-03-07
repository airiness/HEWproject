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
	void init();
	void uninit();
	void update();
	void handleInput();

	Sprite* getSprite(const std::string&);
	//GameObject* getGameObject(const std::string&);
	HANDLE std_h, buffer_h;	//two handles for double buffer
	GameState gameState = INGAME;	//control game state
	CHAR_INFO pixelsOfScene[SCENE_WIDTH * SCENE_HEIGHT]; //screen buffer infor
	//screenScene
	std::vector<GameObject*> objects;
	std::map<std::string, Sprite*> spRes;

	Scene * mainScene;
	InputHandler * inputHandler;
};

