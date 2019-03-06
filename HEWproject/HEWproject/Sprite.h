#pragma once
#include<Windows.h>
#include<string>
#include<vector>
#include<fstream>
class Sprite
{
public:

	Sprite(const std::string&);
	~Sprite();
	CHAR_INFO * charInfo_;		//sprite information
	std::vector<bool> isBlank_;	//is the char_info is blank,remeber every char_info useful or not
	std::string spriteName_;	//sprite name 
	COORD size_;				//sprite size
private:
	//load sprite from bmp file
	int loadSpriteFromFile();
	//change bmp pixel RGB information to char_info

	bool RGBToCharInfo(const RGBTRIPLE&, CHAR_INFO&);
};

