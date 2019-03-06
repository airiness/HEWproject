#include "GameLoop.h"



GameLoop::GameLoop()
{
	init();

}


GameLoop::~GameLoop()
{
	uninit();
}

void GameLoop::gloop()
{

#ifdef _DEBUG
	DebugInfo debuginfo(*mainScene);
#endif // DEBUG



	//fps of the game  16ms 1frame
	//60fps
	const auto frameStep = 16;

	//
	auto previous = GetTickCount();
	auto lag = 0.0;
	auto frameCount = 0;
	auto fps = 0;

	while (true)
	{

		auto current = GetTickCount();
		auto elapsed = current - previous;
		previous = current;
		lag += elapsed;
		if (elapsed!=0)
		{
			fps = frameCount * 1000 / elapsed;
		}

		while (lag>frameStep)
		{
			update();
			lag -= frameStep;
		}
		mainScene->draw();
		++frameCount;
#ifdef _DEBUG
		debuginfo.writeDebugInfo(fps);
#endif // _DEBUG
		mainScene->swap();
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
	//	GetStdHandle(STD_OUTPUT_HANDLE);
	//buffer handle2
	buffer_h = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);

	//set console window name 
	SetConsoleTitle(L"HEWプロジェクト");
	COORD screenSize{ SCENE_WIDTH ,SCENE_HEIGHT };
	mainScene = new Scene(std_h, buffer_h, pixelsOfScene, screenSize);
}

void GameLoop::uninit()
{
}

void GameLoop::update()
{
	switch (gameState)
	{
	case TITLE:
		break;
	case INGAME:
		break;
	case RESULT:
		break;
	default:
		break;
	}
}
