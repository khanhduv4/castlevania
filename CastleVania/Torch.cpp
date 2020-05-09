#include "Torch.h"

CTorch::CTorch()
{
	eType = 3;
	isEnable = true;
	disappearingAnimSet = CAnimationSets::GetInstance()->Get(6);
	isDisappearing = 0;
}

void CTorch::Render()
{
	int ani = 0;
	if (isDisappearing)
	{
		disappearingAnimSet->at(0)->Render(x,y);
		if (disappearingAnimSet->at(0)->IsDone())
			isDisappearing = 0;
	}
	if (!isEnable) return;
	currentFrame = animation_set->at(ani)->Render(x, y, 255);
	RenderBoundingBox();
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
	CGameObject::Update(dt, coObjects);
}