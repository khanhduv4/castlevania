#include "Knight.h"
#include "Define.h"

Knight::Knight()
{
	this->Health = 2;
	isFinish = 0;
	objLife = 0;

	//SetState(/*BLACK_KNIGHT_STATE_WALKING*/);
}

Knight::~Knight()
{
}

void Knight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	CEnemy::Update(dt, coObject);
	//if (!isFinish) {
	//	x += dx;
	//	y += dy;

	//	if (vx > 0 && abs(x - startX) > /*BLACK_KNIGHT_DISTANCE_X*/) {
	//		x = startX + /*BLACK_KNIGHT_DISTANCE_X*/;
	//		vx = -vx;
	//		nx = -1;
	//	}

	//	if (vx < 0 && abs(startX - x) > /*BLACK_KNIGHT_DISTANCE_X*/) {
	//		x = startX - BLACK_KNIGHT_DISTANCE_X;
	//		vx = -vx;
	//		nx = 1;
	//	}
	//}
}

void Knight::Render()
{
	if (!objLife) {
		int ani = 0;
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
