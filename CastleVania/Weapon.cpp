#include "Weapon.h"
#include "Utils.h"



Weapon::Weapon()
{
	isFinish = 0;
	damage = 1;
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

	isFinish = false; // chưa kết thúc
	direction = Direction;

	LastTimeAttack = GetTickCount(); // lưu lại thời điểm lúc vừa tấn công, làm đánh dấu tránh 1 hit đánh nhiều lần cho các object, có health >1.
}

void Weapon::Render()
{
	if (!isFinish)
		return;

}

void Weapon::UpdatePositionFitSimon()
{

}




void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) { 
	if (!isFinish)
		return;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();  
	CalcPotentialCollisions(coObjects, coEvents);  

}


void Weapon::SetFinish(bool b)
{
	isFinish = b;
}

DWORD Weapon::GetLastTimeAttack()
{
	return LastTimeAttack;
}

