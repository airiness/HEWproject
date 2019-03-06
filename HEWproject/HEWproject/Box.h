#pragma once
#include<string>
#include "GameObject.h"
class Box :
	public GameObject
{
public:
	Box(const std::string&);
	Box(COORD &, Sprite &, const std::string&);
	~Box();

	void update();

private:
	std::string name_;	//box name
	int boxNumber;	//choose item of box
	static int chooseNum;
};

