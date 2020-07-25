#include "wAxe.h"



wAxe::wAxe()
{
	damage = 1;
	aniIndex = WEAPON_ANI_SET_AXE;
	ResetAniSet();
}


wAxe::~wAxe()
{
}

void wAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void wAxe::Attack(float X, float Y, int Direction)
{

	// Tai sao bo vx = ... vao ham attack k duoc 
	Weapon::Attack(X+20, Y + 10, Direction);
	vx = WEAPON_SPEED * direction;

}



void wAxe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + AXE_WIDTH;
	bottom = y + AXE_HEIGHT;
}
 

void wAxe::RenderIcon(float X, float Y)
{
	//sprite->DrawFrameFlipX(0, X, Y); 
}
  