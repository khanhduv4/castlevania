#include "GameBoard.h"

CGameBoard *CGameBoard::_instance = NULL;

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
}
void CGameBoard::SetPosition(float x, float y) {
	_x = x;
	_y = y; 
}