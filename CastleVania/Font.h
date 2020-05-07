#ifndef __FONT_H__
#define __FONT_H__

#include "Sprites.h"
#include "Textures.h"
#include "define.h"



class Font
{
private:
	CSprites * _sprite;
	CTextures * _texture;
	
public:
	Font();
	~Font();
	void Draw(float x, float y, const string & s);
};





#endif 



