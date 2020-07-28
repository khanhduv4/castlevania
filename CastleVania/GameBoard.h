#pragma once
#include "Sprites.h"
#include "Simon.h"
#include"Game.h"

#include <d3d9.h>
#include <d3dx9.h>

#define GAMEBOARD_SPRITE_ID 100100

#define POSITION_X_SUBWEAPON 350
#define POSITION_Y_SUBWEAPON 50


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
	void Update(int time, int stage, int enemyHealth);
	void UpdateSubWeapon(int type);
	void SetInitialHP(int HP) {
		this->initHP = HP;
	}
	void SetHP(int HP) {
		this->simonHP = HP;
	}
	void SetScore(int score) {
		this->score = score;
	}
	void ResetBoard(int simonHP, int initHP, int score) {
		this->simonHP = simonHP;
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
	int simonHP;
	int heart;
	int stage;
	int time;
	int bossHP;
	int life;
	vector<CSprite*> _subWeaponSprites;

	int initHP;
};

