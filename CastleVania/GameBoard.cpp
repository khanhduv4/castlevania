#include "GameBoard.h"
#include"Game.h"
#include <string>

CGameBoard* CGameBoard::_instance = NULL;

CGameBoard::CGameBoard() {
	_x = 0;
	_y = 0;
}
CGameBoard::~CGameBoard() {
}
void CGameBoard::Load() {
	_sprite = CSprites::GetInstance()->Get(GAMEBOARD_SPRITE_ID);
}
void CGameBoard::Render() {
	_sprite->Draw(_x, _y, 255, true);
	auto simon = CSimon::getInstance();
	initHP = 16;
	hp = simon->getHealth();
	score = simon->getScore();
	heart = simon->getHeart();

	//Score
	CGame::GetInstance()->Draw(std::to_string(score), 110, 13, 400, 300, D3DCOLOR_XRGB(255, 255, 255));
	// Heart

	// bi de chi roi
	CGame::GetInstance()->Draw(std::to_string(200), 300, 13, 400, 300, D3DCOLOR_XRGB(255, 255, 255));

	//Player HP █
	int baseX = 120, baseY = 30;
	for (int i = this->hp; i < this->initHP; i++) {
		wstring wStr = L"▯";
		CGame::GetInstance()->Draw(wStr, baseX + i * 10, baseY, 300, 300, D3DCOLOR_XRGB(255, 255, 255));
	}
	for (int i = 0; i < this->hp; i++) {
		wstring wStr = L"▮";
		CGame::GetInstance()->Draw(wStr, baseX + i * 10, baseY, 300, 300, D3DCOLOR_XRGB(156, 0, 0));
	}


}
void CGameBoard::SetPosition(float x, float y) {
	_x = x;
	_y = y;
}