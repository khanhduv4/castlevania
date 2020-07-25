#pragma once
#include "Sprites.h"
#include "Simon.h"

#include <d3d9.h>
#include <d3dx9.h>

#define GAMEBOARD_SPRITE_ID 100100

class CGameBoard
{
public:
	~CGameBoard();
	static CGameBoard* GetIntance() {

		if (_instance == NULL)
			_instance = new CGameBoard();
		return _instance;
	}
	void Render();
	void SetPosition(float x, float y);
	void Load();
	void SetInitialHP(int HP) {
		this->initHP = HP;
	}
	void SetHP(int HP) {
		this->hp = HP;
	}
	void SetScore(int score) {
		this->score = score;
	}
	void ResetBoard(int hp, int initHP, int score) {
		this->hp = hp;
		this->score = score;
		this->initHP = initHP;
	}
private:
	CGameBoard();
	static CGameBoard* _instance;
	CSprite* _sprite;
	float _x;
	float _y;
	int score;
	int hp;
	int heart;
	int initHP = 10;
};

