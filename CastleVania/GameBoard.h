#pragma once
#include "Sprites.h"

#define GAMEBOARD_SPRITE_ID 100100

class CGameBoard
{
public : 
	~CGameBoard();
	static CGameBoard* GetIntance() {
		if (_instance == NULL)
			_instance = new CGameBoard();
		return _instance;
	}
	void Render();
	void SetPosition(float x, float y);
	void Load();
private:
	CGameBoard();
	static CGameBoard* _instance;
	CSprite *_sprite;
	float _x;
	float _y;
};

