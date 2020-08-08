#pragma once
#include "Sprites.h"
#include "Simon.h"
#include"Game.h"

#include <d3d9.h>
#include <d3dx9.h>

#define GAMEBOARD_SPRITE_ID 100100
#define GAMEBOARD_SPRITE_BLACK_ID 100101
#define GAMEBOARD_SPRITE_MAIN_MENU 100102

#define POSITION_X_SUBWEAPON 310
#define POSITION_Y_SUBWEAPON 35
 
class CGameBoard
{
public:
	~CGameBoard();
	static CGameBoard* GetInstance() {

		if (_instance == NULL)
			_instance = new CGameBoard();
		return _instance;
	}
	void Render();
	void SetPosition(float x, float y);
	void Load();
	void Update(int dt, int time, int stage); 
	void UpdateSubWeapon(int type);
	void UpdateBossHP(int hp);
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
	void ReloadSubWeaponSprites();
	void SetOver(bool value,string overMsg );

	bool IsStarted() { return isStarted; }
	void Start() { isStarted = true; }
private:
	CGameBoard();
	static CGameBoard* _instance;
	CSprite* _sprite;
	CSprite* _spriteBlack;
	CSprite* _spriteMenu;

	bool isStarted = false;



	float _x;
	float _y;
	int score;
	int simonHP;
	int bossHP;
	int heart;
	int stage;
	int time;

	int life;
	int subWeapon;
	int isRendering = true;
	vector<CSprite*> _subWeaponSprites;

	int overRenderTime = 1500;
	bool isOver = false;
	string overMsg = "";
	int initHP;
	int initBossHP;
};

