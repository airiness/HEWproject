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
	sceneDebug->writeStr("      ");
	sceneDebug->setPos(pos);
	sceneDebug->writeStr(sfps);

}
