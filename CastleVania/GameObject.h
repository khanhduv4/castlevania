#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include"Utils.h"
#include "Sprites.h"
#include "Animations.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define OBJ_LIFE_DISAPPEARING 1
#define OBJ_LIFE_LIVE 0
#define OBJ_LIFE_OUT 2


class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;

	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
	//Refactor
public:
	int id;

	// Object spec
	int Health;
	int direction;
	bool isGravity = 1;
	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;

	int itemId = -1;

	int state;

	DWORD dt;

	LPANIMATION_SET animation_set;

	int objLife;

	bool isCollisionWithSimon = 1;

	int _width;
	int _height;



	bool isFinish;



	void SubHealth(int th);

public:
	void SetPosition(float x, float y) { DebugOut(L"Set simon position:%f %f", this->x, this->y); this->x = x; this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

	void SetWidth(int width) {
		_width = width;
	}
	int GetWidth() {
		return _width;
	}

	void SetHeight(int height) {
		_height = height;
	}
	int GetHeight() {
		return _height;
	}


	void SetObjId(int id) { this->id = id; }
	int GetObjId() { return this->id; }

	int GetState() { return this->state; }

	void RenderBoundingBox();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	void SetAnimation(int id) {
		CAnimationSets* animation_sets = CAnimationSets::GetInstance();
		LPANIMATION_SET ani_set = animation_sets->Get(id);
		this->SetAnimationSet(ani_set);
	}

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);

	CGameObject();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	~CGameObject();
	void GetAABBCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	bool checkAABB(CGameObject* obj);
	virtual bool isCollision(CGameObject* obj); // kiểm tra vũ khí này có va chạm với object kia hay không?

	bool isCollisionObjectWithObject(CGameObject* obj);
	bool GetFinish();
	void SetFinish(bool b);

};

