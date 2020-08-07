#include "wBLue.h"

wBlue::wBlue()
{
	damage = 2;
	aniIndex = WEAPON_ANI_SET_BLUE;
	SetState(BLUE_STATE_BOTTLE);
	ResetAniSet();
}

wBlue::~wBlue()
{
}
void wBlue::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>* coItem)
{
	if (isFinish) return;
	vy += SIMON_GRAVITY * dt;

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CBrick*>((*coObjects)[i]))
			listObject_Brick.push_back((*coObjects)[i]);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(&listObject_Brick, coEvents); // Lấy danh sách các va chạm 
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{

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
			vx = 0;
			SetState(BLUE_STATE_FIRE);
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

	Weapon::Update(dt, coObjects, coItem);

}

void wBlue::Attack(float X, float Y, int Direction)
{
	// Tai sao bo vx = ... vao ham attack k duoc 
	vx = WEAPON_SPEED_X /3.5 * Direction;
	vy = 0.05f;
	Weapon::Attack(X + 20*Direction, Y , Direction);
}



void wBlue::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BLUE_WIDTH;
	bottom = y + BLUE_HEIGHT;
}


void wBlue::RenderIcon(float X, float Y)
{
	//sprite->DrawFrameFlipX(0, X, Y); 
}
void wBlue::Render() { 
	if (!isFinish) {
		if (GetState() == BLUE_STATE_BOTTLE) {
			animation_set->at(1)->Render(x, y);
		}
		else {
			animation_set->at(2)->Render(x, y);
			if (animation_set->at(2)->IsDone())
				isFinish = true;
		}
	}
}