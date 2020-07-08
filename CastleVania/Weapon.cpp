#include "Weapon.h"
#include "Utils.h"
#include "Enemy.h"



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




void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coItems) {
	if (!isFinish)
		return;
	//Refactor Xu ly va cham weapon voi enemy
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;


	coEvents.clear();
	GetAABBCollisions(coObjects, coEvents);
	if (coEvents.size() > 0)
	{
		auto begin = coEvents.begin();
		while (begin != coEvents.end()) {
			CGameObject* object = (*begin)->obj;
			if (dynamic_cast<CEnemy*>(object)) {
				CEnemy* enemy = (CEnemy*)(object);
				++begin;
				if (this->isHit) continue;
				this->isHit = 1;
				float x = 0, y = 0;
				enemy->GetPosition(x, y);
				enemy->SubHealth(damage,coObjects,coItems);

			}
			
		}
	}
}

void Weapon::SetHit(bool isHit) {
	this->isHit = isHit;
}

bool Weapon::IsHit() {
	return isHit;
}

void Weapon::SetFinish(bool b)
{
	isFinish = b;
}

DWORD Weapon::GetLastTimeAttack()
{
	return LastTimeAttack;
}

