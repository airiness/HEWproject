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
//init function
void GameLoop::init()
{
	inithandleBuffers();
	initGameCompanent();
	initGameResource();
}

void GameLoop::uninit()
{
	delete mainScene;
	delete inputHandler;
	delete mainMapInfo;
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
			a->update();
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
