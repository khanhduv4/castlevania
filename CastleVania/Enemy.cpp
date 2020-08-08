#include "Enemy.h"
#include "Brick.h"
#include "Portal.h"
#include"Tilemap.h"
#include "Torch.h"
#include "Sword.h"

#include "UpgradeMorningStar.h"
#include "LargeHeart.h"
#include "SmallHeart.h"
#include "Axe.h"
#include "BossItem.h"
#include "Boomerang.h"
#include "II.h"
#include "Chicken.h"
#include "Money.h"
#include "Blue.h"
#include "GameBoard.h"
#include "CBurningEffect.h"
#include "Knight.h"
#include "Bat.h"
#include "Candle.h"
#include "Elevator.h"
#include "HiddenObject.h"
#include"Grid.h"
#include "PhantomBat.h"

CEnemy::CEnemy()
{
	objLife = OBJ_LIFE_LIVE;
	this->damage = 2;
	isEnable = 1;
	score = 300;
	disappearingAnimSet = CAnimationSets::GetInstance()->Get(6);
}

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	if (health <= 0 && !objLife) {
		objLife = 1;
		Disappear();
	}
	if (isFinish) return;
	// Simple fall down
	if (isGravity) {
		vy += 0.0007f * dt;
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
		x += dx;
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

		//if (nx != 0) vx = 0;
		if (ny != 0) {
			vy = 0;
			if (ny == -1)
				isGrounded = true;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];
}

void CEnemy::Render()
{
	if (objLife == OBJ_LIFE_DISAPPEARING)
	{
		if (dynamic_cast<PhantomBat*>(this)) {
			for (int i = 0; i < 3; i++) {
				disappearingAnimSet->at(0)->Render(x + i * 20, y);
				disappearingAnimSet->at(0)->Render(x + i * 20, y + 30);
			}
			if (phantomDisappearingTime < 0) {
				phantomDisappearingTime = 1000;
				objLife = OBJ_LIFE_OUT;
				isFinish = 1;
				disappearingAnimSet->at(0)->Reset();
			}
		}
		else {
			disappearingAnimSet->at(0)->Render(x, y);
			
		}
		if (disappearingAnimSet->at(0)->IsDone()) {
			objLife = OBJ_LIFE_OUT;
			isFinish = 1;
			disappearingAnimSet->at(0)->Reset();
		}
	}
	if (isHurting2) {
		disappearingAnimSet->at(1)->Render(x, y);
		if (disappearingAnimSet->at(1)->IsDone()) {
			isHurting2 = 0;
			disappearingAnimSet->at(1)->Reset();
		}
	} 
}

void CEnemy::SubHealth(int th, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coItems) {
	CGameObject::SubHealth(th);
	if (dynamic_cast<PhantomBat*>(this)) {
		CGameBoard::GetInstance()->UpdateBossHP(health);
	}
	isHurting2 = 1;
	if (isFinish)
	{
		CSimon::GetInstance()->SetScore(score);
		coItems->push_back(SpawnItem());
	}
}

CItem* CEnemy::SpawnItem() {
	CItem* item = NULL;
	switch (itemId) {
	case ITEM_ID_UPGRADEMORNINGSTAR: {
		item = new UpgradeMorningStar(x, y);
		break;
	}
	case ITEM_ID_LARGEHEART: {
		item = new LargeHeart(x, y);
		break;
	}
	case ITEM_ID_SMALLHEART: {
		item = new SmallHeart(x, y);
		break;
	}
	case ITEM_ID_SWORD: {
		item = new Sword(x, y);
		break;
	}
	case ITEM_ID_BOOMERANG: {
		item = new Boomerang(x, y);
		break;
	}
	case ITEM_ID_II: {
		item = new II(x, y);
		break;
	}
	case ITEM_ID_BLUE: {
		item = new Blue(x, y);
		break;
	}
	case ITEM_ID_CHICKEN: {
		item = new Chicken(x, y);
		break;
	}
	case ITEM_ID_AXE: {
		item = new Axe(x, y);
		break;
	}
	case ITEM_ID_BOSSITEM: {
		item = new BossItem(x, y);
		break;
	}
	case ITEM_ID_MONEY: {
		item = new Money(x, y);
		break;
	}
	default: {
		item = new SmallHeart(x, y);
	}
	}
	return item;
}

void CEnemy::Disappear()
{
	if (objLife) return;
	disappearingAnimSet->at(0)->Reset();
	objLife = OBJ_LIFE_DISAPPEARING;
}