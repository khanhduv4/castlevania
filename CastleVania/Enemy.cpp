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

CEnemy::CEnemy()
{ 
	objLife = OBJ_LIFE_LIVE;
	this->damage = 2;
	isEnable = 1;
	score = 0;
	disappearingAnimSet = CAnimationSets::GetInstance()->Get(6);
}

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* listObject)
{
	if (isFlickering) {
		isFlickering -= dt;
		if (isFlickering < 0)
			isFlickering = 0;
	}
	if (Health <= 0 && !objLife) {
		objLife = 1;
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
	//isFlickering ? CGame::GetInstance()->beginFlickering(false) : NULL;
	//((ani!=-1)&&(!isFinish))?animation_set->at(ani)->Render(x, y,255):NULL;
	//CGame::GetInstance()->endFlickering();
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

void CEnemy::SubHealth(int th, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coItems) {
	CGameObject::SubHealth(th);
	isFlickering = 1200;
	if (isFinish)
	{
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
	default: {
		item = new LargeHeart(x, y);
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
