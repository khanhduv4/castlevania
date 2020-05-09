#include "Weapon.h"
#include "Utils.h"



Weapon::Weapon()
{
	isActive = 0;
}


Weapon::~Weapon()
{
}

int Weapon::GetDirection()
{
	return 0;
}

void Weapon::SetDirection(int Direction)
{}

void Weapon::Attack(float X, float Y, int Direction)
{
	this->x = X;
	this->y = Y;

	isActive = false; // chưa kết thúc
	direction = Direction;

	LastTimeAttack = GetTickCount(); // lưu lại thời điểm lúc vừa tấn công, làm đánh dấu tránh 1 hit đánh nhiều lần cho các object, có health >1.
}

void Weapon::Render()
{
	if (!isActive)
		return;

}

void Weapon::UpdatePositionFitSimon()
{

}


bool Weapon::isCollision(CGameObject* obj)
{	
	return isCollitionObjectWithObject(obj);
}

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) { 
	if (!isActive)
		return;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();  
	CalcPotentialCollisions(coObjects, coEvents);  

}


void Weapon::SetFinish(bool b)
{
	isActive = b;
}

DWORD Weapon::GetLastTimeAttack()
{
	return LastTimeAttack;
}

bool CGameObject::isCollitionObjectWithObject(CGameObject* obj)	// kiểm tra bằng AABB và Sweept AABB
{
	if (checkAABB(obj)) // kiểm tra va chạm bằng AABB trước
		return true;

	LPCOLLISIONEVENT e = SweptAABBEx(obj); // kt va chạm giữa 2 object bằng sweptAABB
	bool res = e->t > 0 && e->t <= 1.0f; // ĐK va chạm
	return res;
}