#include "wSword.h"



wSword::wSword()
{
	damage = 1;
	aniIndex = WEAPON_ANI_SET_SWORD;
	ResetAniSet();
}


wSword::~wSword()
{
}

void wSword::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void wSword::Attack(float X, float Y, int Direction)
{

	// Tai sao bo vx = ... vao ham attack k duoc 
	Weapon::Attack(X+20, Y + 10, Direction);
	vx = WEAPON_SPEED_X * direction;

}



void wSword::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SWORD_WIDTH;
	bottom = y + SWORD_HEIGHT;
}
 

void wSword::RenderIcon(float X, float Y)
{
	//sprite->DrawFrameFlipX(0, X, Y); 
}
  