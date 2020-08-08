#include "Simon.h"

CSimon* CSimon::_Instance = NULL;

CSimon::CSimon() : CGameObject()
{
	// Set default props for simon
	untouchable = score = isClimbableUp = isClimbing = isStair = isFreeze = isSceneSwitching = 0;

	untouchable = 1;

	SetState(SIMON_STATE_IDLE);
	morStar = new MorningStar();

	currentSubWeapon = SIMON_DEFAULT_SUBWEAPON;
	health = SIMON_DEFAULT_HEALTH;

	heart = SIMON_DEFAULT_HEART;
	life = SIMON_DEFAULT_LIFE;

	_width = SIMON_BBOX_WIDTH;
	_height = SIMON_BBOX_HEIGHT;
}

#pragma region Update Props, Ani, State method

void CSimon::UpdateHurting() {
	if (isHurting && GetTickCount() - hurtingTimeCount > SIMON_HURTING_TIME) {
		isHurting = false;
		vx = 0;
		vy = 0;
	}
}

void CSimon::UpdateFreeze()
{
	if (isFreeze && GetTickCount() - freezingTimeCount > SIMON_FREEZE_TIME) {
		freezingTimeCount = 0;
		isFreeze = false;
	}
	else {
		if (isFreeze) {
			vx = 0;
			vy = 0;
			SetState(SIMON_STATE_IDLE);
		}

	}
}

void CSimon::StartOver() {

	this->setSceneSwitching(true,true);
	if (life-- == 0) {
		score = 0;
		life = SIMON_DEFAULT_LIFE; 
		CGame::GetInstance()->SwitchScene(1);
		CGameBoard::GetInstance()->SetOver(true, "GAME OVER");
	}
	else {
		CGame::GetInstance()->StartOver();
	}
	SetPosition(startX, startY);
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coItems)
{
	// Check if scence switching
	if (isSceneSwitching)
		return;

	if (dyingToDiedTime) {
		dyingToDiedTime -= dt;
		if (dyingToDiedTime <= 0)
		{
			StartOver();
			return;
		}
	}
	// check is Dead
	if ((health <= 0 || y > SCREEN_HEIGHT) && GetState() != SIMON_STATE_DIE) {
		SetState(SIMON_STATE_DIE);
		dyingToDiedTime = 500;
	}
	else {
		UpdateHurting();
		UpdateFreeze();
		// Calculate dx, dy 
		CGameObject::Update(dt);

		// Check Attacking

		if (isAttacking) {
			if (weapon == SIMON_ATTACK_MAIN_WEAPON)
				Attack(weapon);
		}

		// Update Weapon

		this->morStar->Update(dt, coObjects, coItems);

		if (subWeapons.size() >= 1) {
			for (int i = 0; i < subWeapons.size(); i++) {
				subWeapons[i]->Update(dt, coObjects, coItems);
			}
		}

		// check Climbable
		if (stair) {
			if (!this->isCollision(stair)) {
				isClimbableUp = isClimbableDown = 0;
			}
		}
	}


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	//if (state != SIMON_STATE_DIE) {
	CalcPotentialCollisions(coObjects, coEvents);
	CalcPotentialCollisions(coItems, coEvents);
	//}
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		// Check hurting
		if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = false;
			isHurting = 0;
		}

		// If attacking and not jumping vx = 0 
		if (isAttacking && !isJumping) {
			vx = 0;
		};
		// Climb stair
		if (isStair) {
			isClimbableDown = isClimbableUp = 1;
			if (isClimbing)
			{
				vx = stairXDirection * SIMON_CLIMBING_SPEED;
				dx = vx * dt;
				nx = stairXDirection;
				vy = stairYDirection * SIMON_CLIMBING_SPEED;
				dy = vy * dt;
				if (y >= SCREEN_HEIGHT - 100 && vy > 0) {
					//Check if out of screen 
					vx = 0;
					vy = 0;
					dx = 0;
					dy = 0;
				}
			}
			else {
				vy = 0;
				vx = 0;
			}
		}
		else {
			vy += SIMON_GRAVITY * dt;
		}
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		//Remove collision with torch and hidden object event & handle collison event
		auto begin = coEvents.begin();
		while (begin != coEvents.end()) {
			if (dynamic_cast<HiddenObject*>((*begin)->obj)) {
				auto obj = dynamic_cast<HiddenObject*>((*begin)->obj);
				if (obj->type == TYPE_STAIR_BEGIN || obj->type == TYPE_STAIR_END) {
					isStair = 0;
					isClimbing = 0;
					startXStair = obj->simonX;
					stairXDirection = obj->direction;
					stairDirection = obj->direction;
					stair = obj;
					if (obj->type == TYPE_STAIR_BEGIN) {
						isClimbableUp = 1;
						isClimbableDown = 0;
						stairYDirection = -1;
					}
					else {
						isClimbableUp = 0;
						isClimbableDown = 1;
						stairYDirection = 1;
					}
				}
			}
			if (!(*begin)->obj->isCollisionWithSimon || (*begin)->obj->GetFinish())
			{
				begin = coEvents.erase(begin);
			}
			else
				++begin;
		}
		// TODO: This is a very ugly designed function!!!!

		//Neu co brick thi uu tien chi brick


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
			if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>((e)->obj);
				this->setSceneSwitching(true);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
				return;
			}
			else if ((dynamic_cast<CBrick*>(e->obj) && e->nx == 0) || dynamic_cast<Elevator*>(e->obj))
			{
				// Kéo simon lên sau khi nhảy
				if (isJumping) {
					y -= 15;
				}
				if (dynamic_cast<Elevator*>(e->obj)) {
					float evx, evy;
					(dynamic_cast<Elevator*>(e->obj))->GetSpeed(evx, evy);
					x += evx * dt * 3;
				}

				this->setJumping(0);
				continue;
			}
			else if ((dynamic_cast<CBrick*>(e->obj) && e->nx != 0))
			{
				vy += SIMON_GRAVITY * dt;
				continue;
			}
			else if (dynamic_cast<CEnemy*>(e->obj)) {

				SetHurt(e);
			}
			else if (dynamic_cast<wBoomerang*>(e->obj)) {
				(e->obj)->SetFinish(true);
			}
			else if (dynamic_cast<CItem*>(e->obj)) {
				y -= 1;
				if (dynamic_cast<BossItem*>(e->obj)) {

					this->setSceneSwitching(true,true);
					score = 0;
					life = SIMON_DEFAULT_LIFE;
					CGame::GetInstance()->SwitchScene(1);
					CGameBoard::GetInstance()->SetOver(true, "YOU WIN !!!");
					SetPosition(startX, startY);
					return;
				}
				HandleCollisionSimonWithItem(e);
				CGameBoard::GetInstance()->UpdateSubWeapon(currentSubWeapon);
				continue;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CSimon::HandleCollisionSimonWithItem(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<UpgradeMorningStar*>(e->obj)) {
		isFreeze = 1;
		freezingTimeCount = GetTickCount();
		morStar->UpgradeLevel();
	}
	else if (dynamic_cast<Sword*>(e->obj)) {
		currentSubWeapon = WEAPON_SWORD;
	}
	else if (dynamic_cast<Axe*>(e->obj)) {
		currentSubWeapon = WEAPON_AXE;
	}
	else if (dynamic_cast<Boomerang*>(e->obj)) {
		currentSubWeapon = WEAPON_BOOMERANG;
	}
	else if (dynamic_cast<Blue*>(e->obj)) {
		currentSubWeapon = WEAPON_BLUE;
	}
	else if (dynamic_cast<LargeHeart*>(e->obj))
		AddHeart(5);
	else if (dynamic_cast<Money*>(e->obj))
		score += dynamic_cast<Money*>(e->obj)->GetScore();
	else if (dynamic_cast<SmallHeart*>(e->obj))
		AddHeart(1);
	else if (dynamic_cast<BossItem*>(e->obj))
		health = SIMON_DEFAULT_HEALTH;
	dynamic_cast<CItem*>(e->obj)->SetFinish(1);
}

void CSimon::Render()
{
	if (isSceneSwitching) {
		return;
	}

	int ani = -1;
	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else
	{
		if (isHurting) {
			ani = SIMON_ANI_HURTING;
		}
		else if (isJumping) {
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
		else if (isStair) {
			if (isAttacking) {
				if (stairYDirection == 1) {
					if (stairXDirection == 1) {
						ani = SIMON_ANI_STAIR_DOWN_ATTACK_RIGHT;
					}
					else {
						ani = SIMON_ANI_STAIR_DOWN_ATTACK_LEFT;
					}
				}
				else {
					if (stairXDirection == 1) {
						ani = SIMON_ANI_STAIR_UP_ATTACK_RIGHT;
					}
					else {
						ani = SIMON_ANI_STAIR_UP_ATTACK_LEFT;
					}
				}
			}
			else if (!isClimbing) {
				if (stairYDirection == 1) {
					if (stairXDirection == 1) {
						ani = SIMON_ANI_STAIR_IDLE_DOWN_RIGHT;
					}
					else {
						ani = SIMON_ANI_STAIR_IDLE_DOWN_LEFT;
					}
				}
				else {
					if (stairXDirection == 1) {
						ani = SIMON_ANI_STAIR_IDLE_UP_RIGHT;
					}
					else {
						ani = SIMON_ANI_STAIR_IDLE_UP_LEFT;
					}
				}
			}
			else
			{
				if (stairYDirection == 1) {
					if (stairXDirection == 1) {
						ani = SIMON_ANI_STAIR_CLIMB_DOWN_RIGHT;
					}

					else {
						ani = SIMON_ANI_STAIR_CLIMB_DOWN_LEFT;
					}
				}
				else {
					if (stairXDirection == 1) {
						ani = SIMON_ANI_STAIR_CLIMB_UP_RIGHT;
					}

					else {
						ani = SIMON_ANI_STAIR_CLIMB_UP_LEFT;
					}
				}

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
	if (untouchable) alpha = 180;
	if (isFreeze)
	{
		// Render 7 mau :D
		CGame::GetInstance()->beginFlickering();

		animation_set->at(ani)->Render(x, y, alpha);
		CGame::GetInstance()->endFlickering();

	}
	else {
		animation_set->at(ani)->Render(x, y, alpha);

	}
	if (isAttacking && animation_set->at(ani)->IsDone()) { isAttacking = 0; }

	if (!morStar->IsFinish()) {
		morStar->Render();
	}
	if (subWeapons.size() >= 1) {
		for (int i = 0; i < subWeapons.size(); i++) {
			if (!subWeapons[i]->IsFinish())
				subWeapons[i]->Render();
		}
	}

}

void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (state == SIMON_STATE_DIE) {
		right = left + SIMON_BBOX_SITTING_WIDTH;
		bottom = top + SIMON_BBOX_SITTING_HEIGHT;
	}
	else {
		if (isSitting) {
			bottom = top + SIMON_BBOX_SITTING_HEIGHT;
		}
		else if (isJumping) {
			bottom = top + SIMON_BBOX_JUMPING_HEIGHT;
		}
		else {
			bottom = top + SIMON_BBOX_HEIGHT;
		}
		right = left + SIMON_BBOX_WIDTH;
	}

}

#pragma endregion

#pragma region Action methods
void CSimon::Die()
{
	isAttacking = 0;
	isStair = 0;
	isHurting = 0;
	untouchable = 0;

}

void CSimon::Climbing(int state) {
	isClimbing = 1;
	if (state == SIMON_STATE_CLIMBING_UP) {
		stairXDirection = stairDirection;
		stairYDirection = -1;
	}
	else {
		stairXDirection = -(stairDirection);
		stairYDirection = 1;
	}

	if (isStair) return;
	x = startXStair;
	isStair = 1;
}

void CSimon::Attack(int weapon) {
	if (isStair)
		isClimbing = 0;
	if (weapon == SIMON_ATTACK_MAIN_WEAPON)
		morStar->Attack(x, y, nx);
	else {
		Weapon* subWeapon = newSubWeapon();
		subWeapon->Attack(x, y, nx);
		SubHeart(subWeapon->GetHeart());
		subWeapons.push_back(subWeapon);
	}
}
#pragma endregion

#pragma region Set Methods

void CSimon::SetSitting(bool status) {
	isSitting = status;
	if (isSitting == 0) {
		y -= 15;
	}
}

void CSimon::SetHurt(LPCOLLISIONEVENT e)
{
	if (untouchable || isHurting) return;
	isAttacking = 0;
	isJumping = 0;
	morStar->SetFinish(1);
	if (isHurting)
		return;
	if (e->nx == 0 && e->ny == 0) // ko có va chạm
		return;



	if (!isStair) // ko "đang tự đi" và ko "đang trên thang" thì bật ra
	{
		hurtingTimeCount = GetTickCount();
		if (e->nx != 0)
		{
			vx = SIMON_WALKING_SPEED * e->nx;
			vy = -SIMON_VJUMP_HURTING;
			isHurting = 1;
		}

		if (e->ny != 0)
		{
			vy = -SIMON_VJUMP_HURTING;
			isHurting = 1;
		}
	}
	else
	{
		isHurting = 1;
	}

	StartUntouchable(); // không cho các object đụng tiếp


	SubHealth(2); // chạm enemy -2 máu
	DebugOut(L"Mau con lai: %d", health);
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
		isClimbing = 0;
		ResetAttackAni();
		morStar->SetHit(0);
		morStar->ResetAnimation();
		this->Attack(weapon);
		this->isAttacking = 1;
		break;
	case SIMON_STATE_SITTING:
		if (this->isSitting) return;
		y += 14;
		this->isSitting = 1;
		break;
	case SIMON_STATE_ON_STAIR: {
		isClimbing = 0;
		isStair = 1;
		break;
	}
	case SIMON_STATE_CLIMBING_UP: {
		Climbing(SIMON_STATE_CLIMBING_UP);
		break;
	}
	case SIMON_STATE_CLIMBING_DOWN: {
		Climbing(SIMON_STATE_CLIMBING_DOWN);
		break;
	}
	case SIMON_STATE_IDLE:
		if (!isHurting)
			vx = 0;
		break;

	case SIMON_STATE_DIE:

		Die();

		break;
	}
}

void CSimon::setSceneSwitching(bool value, bool isFullHealth) {

	stair = NULL;
	isClimbing = 0;
	isClimbableUp = isClimbableDown = 0;
	if (isFullHealth)
		health = SIMON_DEFAULT_HEALTH;
	SetState(SIMON_STATE_IDLE);
	SetSpeed(0, 0);
	this->isSceneSwitching = value;
	isInnewScene = true;
}

void CSimon::SubHeart(int hearts)
{
	heart -= hearts;
}

void CSimon::AddHeart(int hearts) {
	heart += hearts;
}

#pragma endregion

#pragma region Utils

Weapon* CSimon::newSubWeapon()
{
	switch (currentSubWeapon) {
	case WEAPON_SWORD:
		return new wSword();
		break;
	case WEAPON_AXE:
		return new wAxe();
		break;
	case WEAPON_BOOMERANG:
		return new wBoomerang();
		break;

	case WEAPON_BLUE:
		return new wBlue();
		break;
	}

}
void CSimon::Reset()
{
	SetState(SIMON_STATE_IDLE);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}
void CSimon::ResetAttackAni() {

	if (isStair) {
		animation_set->at(SIMON_ANI_STAIR_UP_ATTACK_RIGHT)->Reset();
		animation_set->at(SIMON_ANI_STAIR_UP_ATTACK_LEFT)->Reset();
		animation_set->at(SIMON_ANI_STAIR_DOWN_ATTACK_RIGHT)->Reset();
		animation_set->at(SIMON_ANI_STAIR_DOWN_ATTACK_LEFT)->Reset();
	}
	else {
		animation_set->at(SIMON_ANI_ATTACKING_LEFT)->Reset();
		animation_set->at(SIMON_ANI_ATTACKING_RIGHT)->Reset();
		animation_set->at(SIMON_ANI_SITTING_ATTACK_LEFT)->Reset();
		animation_set->at(SIMON_ANI_SITTING_ATTACK_RIGHT)->Reset();
	}

}

#pragma endregion