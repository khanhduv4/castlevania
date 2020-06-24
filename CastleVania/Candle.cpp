#include "Candle.h"

Candle::Candle()
{
	Health = 1;
	isEnable = true;
	_width = CANDLE_BBOX_WIDTH;
	_height = CANDLE_BBOX_HEIGHT;
	isCollisionWithSimon = 0;
}



void Candle::Render()
{
	if (!objLife) {
		int ani = 0;
		animation_set->at(ani)->Render(x, y, 255);
		//RenderBoundingBox();
	}
	else {
		CEnemy::Render();
	}

}

void Candle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isEnable) {
		l = x;
		t = y;
		r = x + CANDLE_BBOX_WIDTH;
		b = y + CANDLE_BBOX_HEIGHT;
	}
	else {
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (Health <= 0 && !(objLife == OBJ_LIFE_OUT)) {
		objLife = 1;
		Disappear();
	}

}