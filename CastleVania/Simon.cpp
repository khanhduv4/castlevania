#pragma once
#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Simon.h"
#include "Game.h"
#include "Torch.h"
#include "Brick.h"

#include "UpgradeMorningStar.h"
#include "LargeHeart.h"
#include "Portal.h"

#include "MorningStar.h"

CSimon::CSimon(float x, float y) : CGameObject()
{
	untouchable = 0;
	SetState(SIMON_STATE_IDLE);

	this->morStar = new MorningStar();
	Health = 20;
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

	_width = SIMON_BBOX_WIDTH;
	_height = SIMON_BBOX_HEIGHT;
}

int CSimon::getDirection() {
	return this->nx;
}

void CSimon::setSitting(bool status) { 
	isSitting = status;
	if (isSitting == 0) {
		y -= 15;
	}
}

void CSimon::setJumping(bool status)
{
	isJumping = status;
}

void CSimon::setDirection(int direction) {
	this->nx = direction;
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coItems)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	morStar->Update(dt, coObjects);
	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	if (isAttacking && !isJumping) {
		vx = 0;
	};
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	//coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE) {
		CalcPotentialCollisions(coObjects, coEvents);
		CalcPotentialCollisions(coItems, coEvents);
	}
	
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
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
			if (dynamic_cast<CTorch*>((*begin)->obj) || (*begin)->obj->GetFinish())
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
				if (isJumping) {
					y -= 15;
				}
				this->setJumping(0);
				continue;
			} 
			else if (dynamic_cast<CItem*>(e->obj)) {
				if (dynamic_cast<UpgradeMorningStar*>(e->obj))
					morStar->UpgradeLevel();
				else if (dynamic_cast<LargeHeart*>(e->obj))
					AddHeart();

				dynamic_cast<CItem*>(e->obj)->SetFinish(1);

				continue;

			}
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
				return;

			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CSimon::Render()
{
	if (isAttacking) {
		Attack();
	}
	else {
		morStar->SetFinish(1);
	}
	int ani = -1;
	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else
	{
		if (isJumping) {
			if (isAttacking) {
				if (nx > 0)
					ani = SIMON_ANI_ATTACKING_RIGHT;
				else ani = SIMON_ANI_ATTACKING_LEFT;
			}
			else {
				if (nx > 0)
					ani = SIMON_ANI_JUMPING_RIGHT;
				else ani = SIMON_ANI_JUMPING_LEFT;
			}
		}
		else if (isSitting) {
			vx = 0;
			if (isAttacking) {
				if (nx > 0)
					ani = SIMON_ANI_SITTING_ATTACK_RIGHT;
				else ani = SIMON_ANI_SITTING_ATTACK_LEFT;
			}
			else {
				if (nx > 0)
					ani = SIMON_ANI_SITTING_RIGHT;
				else ani = SIMON_ANI_SITTING_LEFT;
			}

		}
		else if (isAttacking) {
			if (nx > 0)
				ani = SIMON_ANI_ATTACKING_RIGHT;
			else ani = SIMON_ANI_ATTACKING_LEFT;
		}
		else if (vx == 0)
		{
			if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
			else ani = SIMON_ANI_IDLE_LEFT;
		}
		else if (vx > 0)
			ani = SIMON_ANI_WALKING_RIGHT;
		else ani = SIMON_ANI_WALKING_LEFT;
	}

	int alpha = 255;
	if (untouchable) alpha = 128; 
	animation_set->at(ani)->Render(x, y, alpha);
	if (isAttacking && animation_set->at(ani)->IsDone()) { isAttacking = 0; morStar->SetActive(0); }
	RenderBoundingBox();

	morStar->Render();
}

void CSimon::Attack() { 
	morStar->Attack(x, y, nx); 
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING:
		if (isSitting) vx = 0;
		else vx = SIMON_WALKING_SPEED * nx;
		break;
	case SIMON_STATE_JUMPING:
		if (this->isJumping) return;
		this->isJumping = 1;
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_ATTACKING:
		if (this->isAttacking) return;
		this->isAttacking = 1; 
		morStar->ResetAnimation();
		animation_set->at(SIMON_ANI_ATTACKING_LEFT)->Reset();
		animation_set->at(SIMON_ANI_ATTACKING_RIGHT)->Reset();
		animation_set->at(SIMON_ANI_SITTING_ATTACK_LEFT)->Reset();
		animation_set->at(SIMON_ANI_SITTING_ATTACK_RIGHT)->Reset();
		break;
	case SIMON_STATE_SITTING:
		if (this->isSitting) return;
		y += 14;
		this->isSitting = 1;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;

	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	}
}

void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (isSitting) {
		bottom = y + SIMON_BBOX_SITTING_HEIGHT;
	}
	else if (isJumping) {
		bottom = y + SIMON_BBOX_JUMPING_HEIGHT;
	}
	else {
		bottom = y + SIMON_BBOX_HEIGHT;
	}
	right = x + SIMON_BBOX_WIDTH;


}

/*
	Reset Mario status to the beginning state of a scene
*/
void CSimon::Reset()
{
	SetState(SIMON_STATE_IDLE);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

void CSimon::Idle() {
	isSitting = isAttacking = isJumping = 0;
}

void CSimon::AddHeart() {
	heart++;
	DebugOut(L"Heart: %d \n", heart);
}