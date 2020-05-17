#include "Enemy.h"
#include "Brick.h"
CEnemy::CEnemy()
{
	objLife = OBJ_LIFE_LIVE;
	disappearingAnimSet = CAnimationSets::GetInstance()->Get(6);
}



void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	if (Health <= 0 && !objLife) {
		objLife = 1;
	}
	if (isFinish) return;
	// Simple fall down
	vy += 0.0007f * dt;

	CGameObject::Update(dt);

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < listObject->size(); i++)
		if (dynamic_cast<CBrick*>((*listObject)[i]))
			listObject_Brick.push_back((*listObject)[i]);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(&listObject_Brick, coEvents); // Lấy danh sách các va chạm 
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) {
			vy = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void CEnemy::Render()
{
	if (objLife == OBJ_LIFE_DISAPPEARING)
	{
		disappearingAnimSet->at(0)->Render(x, y);
		if (disappearingAnimSet->at(0)->IsDone()) {
			objLife = OBJ_LIFE_OUT;
			isFinish = 1;
			disappearingAnimSet->at(0)->Reset();

		}
	}
	else return;
}

void CEnemy::Disappear()
{
	if (objLife) return;
	disappearingAnimSet->at(0)->Reset();
	objLife = OBJ_LIFE_DISAPPEARING;
}
