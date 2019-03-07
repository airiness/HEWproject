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
	Sprite player1sp("panda");
	COORD player1coord = { 5,5 };
	GameObject * player1 = new GameActor(player1coord, player1sp, "player1");
	objects.push_back(player1);

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

		auto current = GetTickCount();
		if (current - fpsLastTime > 50)
		{
			fps = frameCount * 1000 / (current - fpsLastTime);
			fpsLastTime = current;
			frameCount = 0;
		}
		
		if ((current - previous )>= 1000 / 20000)
		{
			previous = current;
			//handle input
			handleInput(*player1);
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

	CONSOLE_CURSOR_INFO info;
	info.dwSize = 1;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(std_h, &info);
	SetConsoleCursorInfo(buffer_h, &info);


	//set console window name 
	SetConsoleTitle(L"HEWプロジェクト");
	//--
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
		for (auto& a : objects)
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

void GameLoop::handleInput(GameObject& obj)
{
	Command * command = inputHandler->handleInput();

	switch (gameState)
	{
	case TITLE:

		break;
	case INGAME:
		if (command)
		{
			command->execute(obj);
		}
		break;
	case RESULT:
		break;
	default:
		break;
	}
}

//get sprite from sprite map
Sprite * GameLoop::getSprite(const std::string& spName)
{
	return spRes.find(spName)->second;
}