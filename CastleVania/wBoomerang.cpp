#include "wBoomerang.h"



wBoomerang::wBoomerang()
{
	damage = 1;
	aniIndex = WEAPON_ANI_SET_BOOMERANG;
	ResetAniSet();
}


wBoomerang::~wBoomerang()
{
}

void wBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void wBoomerang::Attack(float X, float Y, int Direction)
{

	// Tai sao bo vx = ... vao ham attack k duoc 
	Weapon::Attack(X+20, Y + 10, Direction);
	vx = WEAPON_SPEED * direction;

}



void wBoomerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BOOMERANG_WIDTH;
	bottom = y + BOOMERANG_HEIGHT;
}
 

void wBoomerang::RenderIcon(float X, float Y)
{
	//sprite->DrawFrameFlipX(0, X, Y); 
}
  