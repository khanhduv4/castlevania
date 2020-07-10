#include "wSword.h"



wSword::wSword()
{
	damage = 1;
	aniIndex = 8;
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
	Weapon::Attack(X, Y + 10, Direction);
	vx = WEAPON_SPEED * direction;
}



void wSword::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 20;
	bottom = y + 30;
}
 

void wSword::RenderIcon(float X, float Y)
{
	//sprite->DrawFrameFlipX(0, X, Y); 
}
  