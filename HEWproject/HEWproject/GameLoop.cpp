#include "GameLoop.h"

//gameloop constructor
GameLoop::GameLoop()
{
	init();
}
// gameloop deconstructor
GameLoop::~GameLoop()
{
	uninit();
}

// main gameloop
void GameLoop::gloop()
{

#ifdef _DEBUG
	DebugInfo debuginfo(*mainScene);
#endif // DEBUG

	//------init gameobject
	Sprite RedRole("RedRole");
	Sprite BlueRole("BlueRole");
	COORD player1coord = { 5,5 };
	COORD player2coord = { 30,20 };
	GameActor player1(player1coord, RedRole, "player1");
	GameActor player2(player2coord, BlueRole, "player2");
	GameObject * opPlayer1 = &player1;
	GameObject * opPlayer2 = &player2;
	actors.push_back(&player1);
	actors.push_back(&player2);
	pObjects.push_back(opPlayer1);
	pObjects.push_back(opPlayer2);
	//fps of the game  16ms 1frame
	//60fps
	const auto frameStep = 500;

	// time now
	auto previous = 0;
	//last time show fps
	auto fpsLastTime = 0;
	previous = fpsLastTime = GetTickCount();
	//number of frame
	auto frameCount = 0;
	//frame per second
	auto fps = 0;

	while (true)
	{
		//get time now
		auto current = GetTickCount();
		//fps
		if (current - fpsLastTime > 50)
		{
			fps = frameCount * 1000 / (current - fpsLastTime);
			fpsLastTime = current;
			frameCount = 0;
		}
		//make fps 60
		if ((current - previous )>= 1000 / 20000)
		{
			previous = current;
			//handle input
			handleInput(actors);
			//handle update
			update();
			mainScene->draw();
			frameCount++;

#ifdef _DEBUG
			debuginfo.writeDebugInfo(fps);

#endif // _DEBUG
			mainScene->swap();
		}
	}
}

void GameLoop::init()
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
	//--screen size
	COORD screenSize{ SCENE_WIDTH ,SCENE_HEIGHT };

	//init the scene
	mainScene = new Scene(std_h, buffer_h, pixelsOfScene, screenSize);
	inputHandler = new InputHandler();
}

void GameLoop::uninit()
{
	delete mainScene;
	delete inputHandler;
}

void GameLoop::update()
{
	switch (gameState)
	{
	case TITLE:
		break;
	case INGAME:
		for (auto& a : pObjects)
		{
			a->update(mainScene);
		}
		break;
	case RESULT:
		break;
	default:
		break;
	}
}

void GameLoop::handleInput(std::vector<GameActor*>& actors)
{

	if (gameState == TITLE)
	{

	}
	else if (gameState == INGAME)
	{
		vector<Command*> vcommand(actors.size());

		for (auto i = 0; i < actors.size(); i++)
		{
			vcommand[i] = inputHandler->handleInput(*actors[i]);
			if (vcommand[i])
			{
				vcommand[i]->execute(*actors[i]);
			}
		}
	}
	else if (gameState == RESULT)
	{

	}
	else
	{
		
	}
	
}

//get sprite from sprite map
Sprite * GameLoop::getSprite(const std::string& spName)
{
	return spRes.find(spName)->second;
}