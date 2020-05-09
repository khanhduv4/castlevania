#ifndef __BOARD_H__
#define __BOARD_H__

#include "Sprites.h"
#include "Textures.h"
#include "define.h"
#include "Font.h"
#include "Simon.h"
#include "BoardHealth.h"


#define BOARD_DEFAULT_POSITION_X 0.0f
#define BOARD_DEFAULT_POSITION_Y 0.0f

class Board
{
private:
	Font _font;
	BoardHealth * _boardHealth;
	
	CTextures *_texture;
	CSprites * _sprite;
	float x, y;

	string FillNumber(string s, UINT MaxNumber);
	  
	CSprite * _spriteIconDoubleShot;

 public:
	Board(float X, float Y);
	void Render(CSimon * simon, int state, int RemainingTime, CGameObject * boss);
	~Board();

	void SetTexture(CTextures * tex);
};





#endif 


