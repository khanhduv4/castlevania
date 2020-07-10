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
	//Score
	CGame::GetInstance()->Draw(std::to_string(score), 110, 10, 300, 300, D3DCOLOR_XRGB(255, 255, 255));
	//Player HP 	█
	int baseX = 120, baseY = 30;
	for (int i = 0; i < this->hp; i++) {
		wstring wStr = L"▮";
		CGame::GetInstance()->Draw(wStr, baseX + i * 15, baseY, 300, 300, D3DCOLOR_XRGB(255, 0, 255));
	}
	for (int i = this->hp; i < this->initHP; i++) {
		wstring wStr = L"▯";
		CGame::GetInstance()->Draw(wStr, baseX + i * 15, baseY, 300, 300, D3DCOLOR_XRGB(255, 255, 255));
	}
}
void CGameBoard::SetPosition(float x, float y) {
	_x = x;
	_y = y;
}