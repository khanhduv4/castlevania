#include "GameBoard.h"
#include <string> 
 
CGameBoard* CGameBoard::_instance = NULL;

inline void CGameBoard::ReloadSubWeaponSprites() {
	_subWeaponSprites.clear();
	int spriteIds[4]{ 602,603,605,606 };
	for (int i = 0; i < 4; i++) {
		_subWeaponSprites.push_back(CSprites::GetInstance()->Get(spriteIds[i]));
	}
}

CGameBoard::CGameBoard() {
	_x = 0;
	_y = 0;
	initHP = 16;
	stage = 1;
	time = 300;
	heart = 0;
	score = 0;
	subWeapon = -1;
	_subWeaponSprites.clear();

	ReloadSubWeaponSprites();

}
CGameBoard::~CGameBoard() {
}
void CGameBoard::Load() {
	_sprite = CSprites::GetInstance()->Get(GAMEBOARD_SPRITE_ID);
	ReloadSubWeaponSprites();
}
void CGameBoard::Update(int time, int stage, int enemyHealth)
{
	auto simon = CSimon::getInstance();
	simonHP = simon->getHealth();
	score = simon->getScore();
	heart = simon->getHeart();
	life = simon->getLife();
	this->stage = stage;
	this->time = time;

}
void CGameBoard::UpdateSubWeapon(int type)
{
	subWeapon = type;
}
void CGameBoard::Render() {
	_sprite->Draw(_x, _y, 255, true);
	if (!(subWeapon == -1)) {
		_subWeaponSprites[subWeapon]->Draw(POSITION_X_SUBWEAPON, POSITION_Y_SUBWEAPON, 255, true);
	}
	//Score
	CGame::GetInstance()->Draw(std::to_string(score), 110, 13, 400, 300, D3DCOLOR_XRGB(255, 255, 255));
	// Heart
	CGame::GetInstance()->Draw(std::to_string(heart), 400, 34, 450, 80, D3DCOLOR_XRGB(255, 255, 255));
	//Life
	CGame::GetInstance()->Draw(std::to_string(life), 400, 53, 450, 80, D3DCOLOR_XRGB(255, 255, 255));
	// Time
	CGame::GetInstance()->Draw(std::to_string(time), 300, 13, 400, 300, D3DCOLOR_XRGB(255, 255, 255));
	// Stage
	CGame::GetInstance()->Draw(std::to_string(stage), 465, 14, 500, 300, D3DCOLOR_XRGB(255, 255, 255));

	// Player HP █
	int baseX = 120, baseY = 30;
	for (int i = this->simonHP; i < this->initHP; i++) {
		wstring wStr = L"▯";
		CGame::GetInstance()->Draw(wStr, baseX + i * 10, baseY, 300, 300, D3DCOLOR_XRGB(255, 255, 255));
	}
	for (int i = 0; i < this->simonHP; i++) {
		wstring wStr = L"▮";
		CGame::GetInstance()->Draw(wStr, baseX + i * 10, baseY, 300, 300, D3DCOLOR_XRGB(156, 0, 0));
	}
}
void CGameBoard::SetPosition(float x, float y) {
	_x = x;
	_y = y;
}