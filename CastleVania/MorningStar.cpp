#include "MorningStar.h"
#include "Torch.h"
#include "Utils.h"
#include "Game.h"



MorningStar::MorningStar()
{

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(4);
	level = 0;
	currentFrame = 0;
	isActive = 0;
	this->SetAnimationSet(ani_set);

}

MorningStar::~MorningStar()
{
}

void MorningStar::SetActiveBoundingBox(bool isActive) {
	if (isActive) {
		leftBound = x;
		topBound = y;
		if (level == 2) {
			rightBound = x + MORNINGSTAR_LV2_BBOX_WIDTH;
			bottomBound = y + MORNINGSTAR_LV2_BBOX_HEIGHT;
		}
		else { 
			rightBound = x + MORNINGSTAR_LV0_BBOX_WIDTH;
			bottomBound = y + MORNINGSTAR_LV0_BBOX_HEIGHT;
		}

	}
	else {
		leftBound = 0;
		topBound = 0;
		rightBound = 0;
		bottomBound = 0;
	}
}

void MorningStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Weapon::Update(dt, coObjects);
}

void MorningStar::Render()
{
	if (!isActive) return;
	ani = 0;
	switch (level) {
	case 0: {
		ani = MORNINGSTAR_ANI_LEVEL0_LEFT;
		if (direction == 1)
			ani = MORNINGSTAR_ANI_LEVEL0_RIGHT;
		break;
	}
	case 1: {
		ani = MORNINGSTAR_ANI_LEVEL1_LEFT;
		if (direction == 1)
			ani = MORNINGSTAR_ANI_LEVEL1_RIGHT;
		break;
	}
	case 2: {
		ani = MORNINGSTAR_ANI_LEVEL2_LEFT;
		if (direction == 1)
			ani = MORNINGSTAR_ANI_LEVEL2_RIGHT;
	}

	}

	int alpha = 255;
	currentFrame = animation_set->at(ani)->Render(x, y, alpha);
	if (animation_set->at(ani)->IsDone()) isHit = false;

	//RenderBoundingBox();

}

void MorningStar::Attack(float X, float Y, int Direction)
{
	isActive = 1;
	Weapon::Attack(X, Y, Direction);
	switch (currentFrame) {

	case 0: {
		if (direction == -1) {
			x += (SIMON_WIDTH + 10);
		}
		else {
			x -= (13);
		}
		y += 12;

		SetActiveBoundingBox(false);

		break;
	}
	case 1: {
		if (direction == -1) {
			x += (SIMON_WIDTH - 2);
		}
		else {
			x -= 30;
		}
		y += 7;
		SetActiveBoundingBox(false);
		break;
	}
	case 2: {
		if (direction == 1) {
			x += (SIMON_WIDTH + 10);
		}
		else {
			if (level == 2) {
				x -= (SIMON_WIDTH + 12 + 34);
			}
			else x -= (SIMON_WIDTH + 12);
		}
		if (level == 1 || level == 2) y += 5;

		y += 10;
		SetActiveBoundingBox(true);
		break;
	}
	}
	UpdatePositionFitSimon();
}

void MorningStar::UpdatePositionFitSimon()
{

}

void MorningStar::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = leftBound;
	top = topBound;
	right = rightBound;
	bottom = bottomBound;

}

void MorningStar::RenderIcon(float X, float Y)
{
}

void MorningStar::UpgradeLevel()
{
	if (level >= 2)
		return;
	level++;
	if (isActive == false) // nếu chưa đánh xong mà update thì phải update lại frame để sau khi Freezed xong sẽ chạy tiếp
	{
	}


}

int MorningStar::GetLevel()
{
	return level;
}

bool MorningStar::isCollision(CGameObject* obj)
{
	return Weapon::isCollision(obj);
}
