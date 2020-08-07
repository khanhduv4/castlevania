#include "Weapon.h"
#include "Utils.h"
#include "Enemy.h"
#include "wBlue.h"



Weapon::Weapon()
{
	isFinish = 0;
	isHit = 0;
	damage = 1;
	heart = 1;
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
	SetPosition(X, Y);

	isFinish = false; // chưa kết thúc
	direction = Direction;
	 
	LastTimeAttack = GetTickCount(); // lưu lại thời điểm lúc vừa tấn công, làm đánh dấu tránh 1 hit đánh nhiều lần cho các object, có health >1.
}

void Weapon::Render()
{
	if (isFinish)
		return;
	else {
		if (direction == -1)
		animation_set->at(1)->Render(x, y, 255);
		else animation_set->at(2)->Render(x, y, 255);
	}
	//RenderBoundingBox();

}

void Weapon::UpdatePositionFitSimon()
{

}

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coItems) {
	if (isFinish)
		return;
	CGameObject::Update(dt); // update dt,dx,dy 
	x += dx;
	y += dy;
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	if (x < cx || x > cx + SCREEN_WIDTH) {
		isFinish = 1;
		return;
	}

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
			if (object->isFinish) {
				++begin;
				continue;
			}
			if (dynamic_cast<CEnemy*>(object) && dynamic_cast<CEnemy*>(object)->isEnable) {
				CEnemy* enemy = (CEnemy*)(object);
				++begin;
				if (this->isHit) continue;
				this->isHit = 1;
				float x = 0, y = 0;
				enemy->GetPosition(x, y);
				enemy->SubHealth(damage,coObjects,coItems);
				if (dynamic_cast<wBlue*>(this)) {
					this->isFinish = true;
				}
			}
			else {
				++begin;
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

