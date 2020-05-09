#include "CBurningEffect.h"

CBurningEffect::CBurningEffect(float X, float Y)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(6);

	this->SetAnimationSet(ani_set);
	this->x = X;
	this->y = Y;
}

void CBurningEffect::Render()
{
	if (animation_set->at(0)->IsDone()) return;
	animation_set->at(0)->Render(x, y, 255);
}



void CBurningEffect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = 0;
	right = 0;
	bottom = 0;
	top = 0;
}
