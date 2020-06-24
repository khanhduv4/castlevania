#include "Item.h"
#include "Brick.h"

CItem::CItem()
{ 
	TimeDisplayed = 0;
	TimeWaitMax = 0;
	TimeDisplayMax = 0;
	TimeWaited = 0;
	isFinish = 0;
	Health = 1;
}


CItem::~CItem()
{
	 
}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT> *listObject)
{ 
	if (isFinish) return;
	// Simple fall down
	vy += 0.0007f * dt;

	//if (isWaitingDisplay())
	//{
	//	TimeWaited += dt;
	//	return;
	//}

	//TimeDisplayed += dt;
	//if (TimeDisplayed >= TimeDisplayMax)
	//{
	//	isFinish = true;
	//	return;
	//}

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

void CItem::Render()
{
	//if (isWaitingDisplay())
	//{ 
	//	return;
	//}
	if (isFinish) return;
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();

}

bool CItem::isWaitingDisplay()
{
	return TimeWaited < TimeWaitMax;
}
 




