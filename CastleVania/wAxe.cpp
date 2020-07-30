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
#define AXE_SPEED_Y 0.0007

void wAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += AXE_SPEED_Y * dt;

	Weapon::Update(dt, coObjects, NULL);
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
  