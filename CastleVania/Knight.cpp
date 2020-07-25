#include "Knight.h"
#include "Define.h"
#include "HiddenObject.h"
Knight::Knight(int maxLeft, int maxRight)
{
	isFront = true;
	this->Health = 2;
	isFinish = 0;
	objLife = 0;
	ani = 1;
	maxXleft = maxLeft;
	maxXright = maxRight;

	//SetState(/*BLACK_KNIGHT_STATE_WALKING*/);
}

Knight::~Knight()
{
}

void Knight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	CEnemy::Update(dt, coObject);
	vx = 0.09f * nx;
	if (nx == 1) {
		if (x >= maxXright) {
			nx = -nx;
			ani = 0;
		}
	}
	else {
		if (x <= maxXleft) {
			ani = 1;
			nx = -nx;
		}
	}




}

void Knight::Render()
{
	if (!objLife) {
		animation_set->at(ani)->Render(x, y, 255);
		RenderBoundingBox();
	} else
	CEnemy::Render();
}

void Knight::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
		left = x;
		top = y;
		right = left + (isFinish ? 0 : 32);
		bottom = top + (isFinish ? 0 : 64); 
}

void Knight::SetState(int state)
{
	CEnemy::SetState(state);
	switch (state)
	{
	//case BLACK_KNIGHT_STATE_DIE:
	//	isFinish = true;
	//	isEnable = false;
	//	break;
	//case BLACK_KNIGHT_STATE_WALKING:
	//	vx = -BLACK_KNIGHT_WALKING_SPEED;
	//	nx = -1;
	}
}
