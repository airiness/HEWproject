#include "Box.h"

Box::Box(const std::string& boxName)
	:name_(boxName)
{
}

Box::Box(COORD & pos_, Sprite & sp_, const std::string &boxname)
	:GameObject(pos_,sp_),name_(boxname)
{
}


Box::~Box()
{
}


void Box::update()
{

}