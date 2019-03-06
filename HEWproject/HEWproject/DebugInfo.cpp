#include "DebugInfo.h"

DebugInfo::DebugInfo(Scene & scene_)
	:sceneDebug(&scene_)
{
}

DebugInfo::~DebugInfo()
{
}

void DebugInfo::writeDebugInfo( const int fps)
{
	std::string sfps;
	std::stringstream ss;

	ss << "fps:" << fps;
	ss >> sfps;
	COORD pos = { 0,0 };
	sceneDebug->setPos(pos);
	sceneDebug->writeStr(sfps);

}
//
//void DebugInfo::writeDebugInfoToScene()
//{
//	for (size_t i = 0; i < debugBoardSize.X; i++)
//	{
//		for (size_t j = 0; j < debugBoardSize.Y; j++)
//		{
//			if (isBlank[j * debugBoardSize.X + i] == true)
//			{
//				scenePixels[j *SCENE_WIDTH + i] = debugInformation[j * debugBoardSize.X + i];
//			}
//		}
//	}
//}
