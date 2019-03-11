#include "Sprite.h"



Sprite::Sprite()
	:charInfo_(nullptr), size_({ 0,0 })
{
}

Sprite::Sprite(const std::string& filename)
	:spriteName_(filename),charInfo_(nullptr),size_({0,0})
{
	loadSpriteFromFile();
}

Sprite::Sprite(const Sprite & rhs)
	:size_(rhs.size_),spriteName_(rhs.spriteName_),isBlank_(rhs.isBlank_)
{
	charInfo_ = new CHAR_INFO[rhs.size_.X * rhs.size_.Y];
	for (size_t i = 0; i < rhs.size_.X * rhs.size_.Y; i++)
	{
		charInfo_[i] = rhs.charInfo_[i];
	}
}

Sprite & Sprite::operator=(Sprite rhs)
{
	swap(*this, rhs);
	return *this;
}

Sprite::~Sprite()
{
	delete[] charInfo_;
}

void Sprite::swap(Sprite & lhs, Sprite & rhs)
{
	using std::swap;
	swap(lhs.charInfo_, rhs.charInfo_);
	swap(lhs.isBlank_, rhs.isBlank_);
	swap(lhs.size_, rhs.size_);
	swap(lhs.spriteName_, rhs.spriteName_);
}

int Sprite::loadSpriteFromFile()
{
	// file path
	std::string path{ "Resource\\" };
	path = path + spriteName_ + ".bmp";
	//open the bmp file
	std::fstream fs(path, std::ios::binary | std::ios::in);
	//if fail return -1
	if (!fs)
	{
		return -1;
	}
	//file header
	BITMAPFILEHEADER bmpFileh;
	BITMAPINFOHEADER bmpInfoh;
	//read file header
	fs.read(reinterpret_cast<char*>(&bmpFileh), sizeof BITMAPFILEHEADER);
	//if not bmp file return -1
	if (bmpFileh.bfType != 'MB')
	{
		return -1;
	}
	//red bmp info header
	fs.read(reinterpret_cast<char*>(&bmpInfoh), sizeof BITMAPINFOHEADER);
	//bmp size (pixil)
	int bmpHeight = bmpInfoh.biWidth;
	int bmpWidth = bmpInfoh.biHeight;
	// pixil num of bmp 
	int pixilNum = bmpHeight * bmpWidth;
	//color information of bmp file
	RGBTRIPLE * pColors = new RGBTRIPLE[pixilNum];
	fs.read(reinterpret_cast<char*>(pColors), sizeof(RGBTRIPLE) * pixilNum);
	//save bmp size
	size_.X = bmpHeight;
	size_.Y = bmpWidth;

	charInfo_ = new CHAR_INFO[pixilNum];
	for (size_t i = 0; i < pixilNum; i++)
	{
		isBlank_.push_back(RGBToCharInfo(*(pColors + i), *(charInfo_ + i)));
	}

	fs.close();
	return 0;
}

bool Sprite::RGBToCharInfo(const RGBTRIPLE & rgb, CHAR_INFO & charInfo)
{
	charInfo.Attributes = 0x00;
	charInfo.Char.UnicodeChar = ' ';

	if (rgb.rgbtRed == 0x00)
	{
		if (rgb.rgbtGreen == rgb.rgbtBlue && rgb.rgbtGreen == 0x00)
		{
			return false;
		}
		else
		{
			charInfo.Attributes = 0x0f;
			charInfo.Char.UnicodeChar = (rgb.rgbtGreen << 8) + rgb.rgbtBlue;
		}
	}
	else
	{
		int colorSum = rgb.rgbtBlue + rgb.rgbtGreen + rgb.rgbtRed;
		short tmp = 0x00;
		if (rgb.rgbtBlue >> 7 == 1)
		{
			tmp++;
		}
		if (rgb.rgbtGreen >> 7 == 1)
		{
			tmp += 0x2;
		}
		if (rgb.rgbtRed >> 7 == 1)
		{
			tmp += 0x4;
		}
		if (colorSum > 128 * 3)
		{
			tmp += 0x8;
		}
		charInfo.Attributes = tmp << 4;;
	}

	return true;
}
