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
void wAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects,vector<LPGAMEOBJECT>* coItem)
{
	vy += SIMON_GRAVITY*dt;

	Weapon::Update(dt, coObjects, coItem);
}

void wAxe::Attack(float X, float Y, int Direction)
{
	// Tai sao bo vx = ... vao ham attack k duoc 
	vx = WEAPON_SPEED_X/3 * Direction;
	vy = -WEAPON_SPEED_Y;
	Weapon::Attack(X+20, Y + 10, Direction);
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
  