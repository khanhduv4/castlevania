#include "wSword.h"



wSword::wSword()
{
	damage = 2;
}


wSword::~wSword()
{
}

void wSword::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{  
	//if (!isStart) // vũ khí chưa bắt đầu thì tiếp tục update và thoát
	//{
	//	Weapon::UpdateIsStart(dt);
	//	return;
	//}

	//if (!camera->checkObjectInCamera(x, y, (float)GetWidth(), (float)GetHeight())) // xử lí ra khỏi cam thì kết thúc 
	//{
	//	isFinish = true;
	//	return;
	//}
	// 
	CGameObject::Update(dt); // update dt,dx,dy 
	x += dx;
	 
} 

void wSword::Attack(float X, float Y, int Direction)
{
	Weapon::Attack(X, Y + 10, Direction);
	vx = DAGGER_SPEED * direction;
}

void wSword::Render() {

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
  