/*
author:zhang ruisong
date:2019.3.9
sprite class
*/
#pragma once
#include<Windows.h>
#include<string>
#include<vector>
#include<fstream>
class Sprite
{
public:
	Sprite();
	Sprite(const std::string& filename);
	Sprite(const Sprite& rhs);
	Sprite & operator=(Sprite rhs);
	~Sprite();
	//use your own fucking swap!!!!!!!!!!!!!!!!!!!
	//don't use std::swap to your own class!!!!!!!!!
	//i spended at least 3hours here, oh my fuck!!
	//please remember!!!
	void swap(Sprite & lhs, Sprite & rhs);
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

