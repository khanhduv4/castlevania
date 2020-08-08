#include "wBone.h"
#include "Weapon.h"
#include"Simon.h"

wBone::wBone(int direction, float x, float y)
{
	aniIndex = WEAPON_ANI_SET_BONE;
	ResetAniSet();
	this->x = x + (direction > 0 ? 10 : -10);
	this->y = y;
	vx = BONE_SPEED_X * direction;
	vy = -WEAPON_SPEED_Y;
	isFinish = false;
	objLife = OBJ_LIFE_DISAPPEARING;
}

wBone::~wBone()
{
}

void wBone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += SIMON_GRAVITY * dt;
	x += vx * dt;
	y += vy * dt;
	if (isCollision(CSimon::GetInstance())) {
		CSimon::GetInstance()->SetHurt(new CCollisionEvent(1, 1, 1));
	}
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	if (x < cx || x > cx + SCREEN_WIDTH) {
		isFinish = 1;
		return;
	}
}

void wBone::Render() {
	animation_set->at(0)->Render(x, y, 255);
}

void wBone::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BONE_WIDTH;
	bottom = y + BONE_HEIGHT;
}

