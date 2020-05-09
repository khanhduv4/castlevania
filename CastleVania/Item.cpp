#include "Item.h"
#include "Brick.h"

CItem::CItem()
{ 
	TimeDisplayed = 0;
	TimeWaitMax = 0;
	TimeDisplayMax = 0;
	TimeWaited = 0;
	isFinish = 0;
}


CItem::~CItem()
{
	 
}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT> *listObject)
{ 
	

	if (isWaitingDisplay())
	{
		TimeWaited += dt;
		return;
	}

	TimeDisplayed += dt;
	if (TimeDisplayed >= TimeDisplayMax)
	{
		isFinish = true;
		return;
	}

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

		//Remove collision with torch event
		auto begin = coEvents.begin();
		while (begin != coEvents.end()) {
			if (dynamic_cast<CBrick*>((*begin)->obj))
				begin = coEvents.erase(begin);
			else
				++begin;
		}

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) {
			vy = 0;
		}

		// 
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj)) {
				// Kéo simon lên sau khi nhảy

			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void CItem::Render()
{
	if (isWaitingDisplay())
	{ 
		return;
	}

	//if (IS_DEBUG_RENDER_BBOX)
	//	RenderBoundingBox();
}

bool CItem::isWaitingDisplay()
{
	return TimeWaited < TimeWaitMax;
}
 



bool CItem::GetFinish()
{
	return isFinish;
}

void CItem::SetFinish(bool b)
{
	isFinish = b;
}
