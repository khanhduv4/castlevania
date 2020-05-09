#include "MorningStar.h"
#include "Torch.h"
#include "Utils.h"
#include "Game.h"



MorningStar::MorningStar()
{

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(4);

	currentFrame = 0;
	this->SetAnimationSet(ani_set);

}

MorningStar::~MorningStar()
{
}

//void MorningStar::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//
//
//		CGameObject::Update(dt);
//
//		for (UINT i = 0; i < coObjects->size(); i++)
//		{
//						
//			
//			float l1, t1, r1, b1;
//			GetBoundingBox(l1, t1, r1, b1);
//			float l2 = 170, t2 = 276, r2 = 170 + 32, b2 = 276 + 64;
//
//			
//		
//			if (CGame::AABBCheck(l1, t1, r1, b1, l2, t2, r2, b2))
//			{
//			 if (dynamic_cast<CTorch*>(coObjects->at(i))) {
//				 CTorch* torch = dynamic_cast<CTorch*>(coObjects->at(i));
//					if (torch->isEnable) {
//						torch->isEnable = false;
//					}
//			}
//			
//		}
//	}
//}
//

void MorningStar::SetActiveBoundingBox(bool isActive) {
	if (isActive) {
		leftBound = x;
		topBound = y;
		rightBound = x + 46;
		bottomBound = y + 16;
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

	int ani = MORNINGSTAR_ANI_LEVEL0_LEFT;
	if (direction == 1)
		ani = MORNINGSTAR_ANI_LEVEL0_RIGHT;
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
			x -= (SIMON_WIDTH + 12);
		}
		y += 10;
		SetActiveBoundingBox(true);
		break;
	}
	}
	int alpha = 255;
	currentFrame = animation_set->at(ani)->Render(x, y, alpha);
	RenderBoundingBox();

}

void MorningStar::Attack(float X, float Y, int Direction)
{
	isActive = 1;
	Weapon::Attack(X, Y, Direction);
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
