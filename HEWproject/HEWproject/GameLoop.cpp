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
#ifdef _DEBUG
		//fps
		if (current - fpsLastTime > 50)
		{
			fps = frameCount * 1000 / (current - fpsLastTime);
			fpsLastTime = current;
			frameCount = 0;
		}
#endif // DEBUG_


		//make fps 60
		if ((current - previous )>= 1000 / 160)
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
//unitit function
void GameLoop::uninit()
{
	delete mainScene;
	delete inputHandler;
	delete mainMapInfo;
}
//call update function every frame
void GameLoop::update()
{
	if (gameState == TITLE)
	{
		//setStateToBegin();
		objTitleAndResult->update();
	}
	if (gameState == INGAME)
	{
		if (gameTimeInited == false)
		{
			gameTimeNow = GetTickCount();
			gameTimeInited = true;
		}
		auto tmpTime = GetTickCount();
		gameTime-=(tmpTime - gameTimeNow);
		if (gameTime <= 0)
		{
			gameState = RESULT;
		}
		gameTimeNow = tmpTime;
		mainMapInfo->update();
		//for (auto& a : pObjects)
		//{
		//	a->update();
		//}
		actors[0]->update(*actors[1]);
		actors[1]->update(*actors[0]);
		
	}
	if (gameState == RESULT)
	{
		reAllComponent();
		objTitleAndResult->update();
	}
}

void GameLoop::reAllComponent()
{
}

void GameLoop::handleInput(std::vector<GameActor*>& actors)
{

	if (gameState == TITLE)
	{
		if (inputHandler->inputSth(VK_SPACE))
		{
			gameState = INGAME;
		}
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
		if (inputHandler->inputSth(VK_SPACE))
		{
			gameState = TITLE;;
		}
	}
	
}
