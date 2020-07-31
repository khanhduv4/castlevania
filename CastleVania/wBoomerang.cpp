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

void wBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT> * coItems)
{

	if (isFinish)
		return;
	if (abs(x - startX) > BOOMERANG_MAX_DISTANCE && vx / direction > 0)
		vx = -vx;
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
				//this->isHit = 1;
				float x = 0, y = 0;
				enemy->GetPosition(x, y);
				enemy->SubHealth(damage, coObjects, coItems);
			}else if (dynamic_cast<CSimon*>(object)) {
				//check simon
				isFinish = true;
			}
			else {
				++begin;
			}
		}
	}
}

void wBoomerang::Attack(float X, float Y, int Direction)
{

	// Tai sao bo vx = ... vao ham attack k duoc 

	Weapon::Attack(X+20, Y + 10, Direction);
	vx = WEAPON_SPEED_X/2 * direction;

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
  