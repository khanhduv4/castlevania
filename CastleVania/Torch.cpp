#include "Torch.h"

CTorch::CTorch()
{
	health = 1;
	isEnable = true;
	_width = TORCH_BBOX_WIDTH;
	_height = TORCH_BBOX_HEIGHT;
	isCollisionWithSimon = 0;
}



void CTorch::Render()
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

void CTorch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isEnable) {
		l = x;
		t = y;
		r = x + TORCH_BBOX_WIDTH;
		b = y + TORCH_BBOX_HEIGHT;
	}
	else {
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
}

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (health <= 0 && !(objLife == OBJ_LIFE_OUT)) {
		objLife = 1;
		Disappear();
	}

}