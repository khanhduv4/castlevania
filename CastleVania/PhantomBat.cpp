#include <time.h>
#include "Define.h"

#include "PhantomBat.h"
#include "Simon.h"

PhantomBat::PhantomBat()
{

	this->health = 2;
	this->damage = 2;


	srand(time(0));

	delayTime = (rand()) % 500 + 500;
	chaseTime = (rand()) % 500 + 500;
	//bossDeadEffect = new BossDeadEffect(1);
	isFlyToRandomPos = true;
	isFlyToSimonPos = true;
	isFront = 1;
	phantomDisappearingTime = 1000;
	waitTime = 0;
	hurtTime = PHANTOM_BAT_HURT_TIME;
	isHurted = false;
	isGravity = 0;
	introTime = 2000;
	simonPos.x = -1;
	distance = -1;
	isFinish = 0;
	isEnable = false;

	SetState(PHANTOM_BAT_STATE_IDLE);
}

PhantomBat::~PhantomBat()
{

}
void PhantomBat::makeRandomCurve() {
	int screenWidth = SCREEN_WIDTH;
	int screenHeight = SCREEN_HEIGHT;
	float simonX, simonY;
	CSimon::GetInstance()->GetPosition(simonX, simonY);
	simonY -= 50; 
	int desX = x < simonX ? x + (20) : x - 20;
	int desY = y < simonY ? y + 300 + rand() % 200 : -(y + 300 + rand() % 400);
	
	float b = float(rand() % 10) / 10;;
	float a = -b*(x-desX) / (x * x - desX * desX);
	aCurve = a;
	bCurve = b;
}
float PhantomBat::calculatevYCurve(int x) {
	float y = (2 * aCurve * x + bCurve);
	return y;
}
void PhantomBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (health <= 0 && !(objLife == OBJ_LIFE_OUT)) {
		objLife = 1;
		Disappear();
	}

	float simonX, simonY;
	CSimon::GetInstance()->GetPosition(simonX, simonY);
	CSimon* simon = CSimon::GetInstance();
	if (objLife == OBJ_LIFE_DISAPPEARING) {
		phantomDisappearingTime -= dt;
	}
	if (simon->x >= 1300) {
		SetState(PHANTOM_BAT_STATE_FLYING);

		isEnable = true;
	}
	if (!isEnable || isFinish) return;

	if (delayTime > 0) { delayTime -= dt; vx = 0; vy = 0; return; }
	else if (delayTime <= 0 && !isChasing) {
		isChasing = true;
		chaseTime = (rand()) % 700 + 800;
		makeRandomCurve();
		if (x < simon->x) {
			vx = .2f;
		}
		else vx = -.2f;
	}
	if (y <= 300) {
		y -= dt * vy;
		vy = abs(vy);
	}
	else if (y > SCREEN_HEIGHT - 50) {
		vy = -abs(vy); 
	}
	if (x > 1400) { 
		vx = -abs(vx);
	}
	else if (x < (1400 - SCREEN_WIDTH + 100) ) { 
		vx = abs(vx);
	}

	x += dt * vx;
	y += dt * vy;
	if (isChasing) {
		vy = float(calculatevYCurve(x));
		chaseTime -= dt;

		//DebugOut(L"X Bat = %f Y Bat  = %f", x, vy);
		if (chaseTime <= 0) {
			isChasing = false;
			delayTime = (rand()) % 500 + 1000;
		}

	}
	
	//CEnemy::Update(dt, coObjects);

}

void PhantomBat::Render()
{
	if (!isFinish) {
		int ani = 0;
		switch (state)
		{
		case PHANTOM_BAT_STATE_IDLE:
		{
			ani = PHANTOM_BAT_ANI_IDLE;
			break;
		}
		case PHANTOM_BAT_STATE_FLYING:
		{
			ani = PHANTOM_BAT_ANI_FLYING;
			break;
		}
		default:
			break;
		}

		animation_set->at(ani)->Render(x, y);
		//RenderBoundingBox();
	}
	//collisionEffect->Render();

	CEnemy::Render();

}

void PhantomBat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!isFinish && state == PHANTOM_BAT_STATE_FLYING) {
		left = x;
		top = y;
		right = left + PHANTOM_BAT_WIDTH;
		bottom = top + PHANTOM_BAT_HEIGHT;
	}
	else {

		left = x;
		top = y;
		right = left + 0;
		bottom = top + 0;

	}
}

void PhantomBat::SetState(int state)
{
	CEnemy::SetState(state);
}

void PhantomBat::SubHealth(int th)
{
	CGameObject::SubHealth(th);
}

void PhantomBat::CalculateSimonPos(DWORD dt)
{
	float simonX, simonY;

	CSimon::GetInstance()->GetPosition(simonX, simonY);

	if (simonPos.x < 0) {
		simonPos = D3DXVECTOR2(simonX, simonY);
	}
	else if (chaseTime > 0) {
		chaseTime -= dt * 0.001;
		simonPos = D3DXVECTOR2(simonX, simonY);
	}

	if (isFlyToSimonPos == true)
	{
		distance = sqrt(
			pow(simonPos.x - x, 2) +
			pow(simonPos.y - y, 2));

		nx = (simonPos.x - x) / distance;
		ny = (simonPos.y - y) / distance;
	}
	if (isFlyToSimonPos == false)
	{
		batPos = D3DXVECTOR2(x, y);
	}
}

void PhantomBat::Fly(DWORD dt)
{
	if (abs(batPos.x - simonPos.x) > 10)
	{
		vx = 0.10;
		vy = 0.09;
	}
	x += nx * vx * dt;
	y += ny * vy * dt;

	if (sqrt(pow(simonPos.x - x, 2) + pow(simonPos.y - y, 2)) >= distance)
	{
		isFlyToSimonPos = false;
		x = simonPos.x;
		y = simonPos.y;
	}
	this->SetPosition(x, y);
	SetState(PHANTOM_BAT_STATE_FLYING);
}

void PhantomBat::RandomPos()
{
	random.x = rand() % (200) + 510;
	random.y = rand() % (25) + 60;
	isFlyToRandomPos = false;
	waitTime = PHANTOM_BAT_WAIT_TIME;
	vx = 0.065;
	vy = 0.06;
}

bool PhantomBat::Intro(DWORD dt)
{
	if (introTime > 0)
	{
		if (introTime > 1500)
			SetState(PHANTOM_BAT_STATE_IDLE);
		else
			SetState(PHANTOM_BAT_STATE_FLYING);
		introTime -= dt;
		return true;
	}
	else
		return false;
}

void PhantomBat::CheckHPChange()
{
	if (previousHP != health)
	{
		if (health <= 0)
		{

			isEnable = false;
			//isDeadth = true;
			//bossDeadEffect->Enable();
			return;
		}
		else
		{
			isHurted = true;
			previousHP = health;
			return;
		}
	}
}

void PhantomBat::CheckHurtTime(DWORD dt)
{
	SetState(PHANTOM_BAT_STATE_HURT);
	hurtTime -= dt;
	if (hurtTime <= 0)
	{
		isHurted = false;
		hurtTime = PHANTOM_BAT_HURT_TIME;
	}
}

void PhantomBat::FlyToRandomPos(DWORD dt)
{
	distance = sqrt(
		pow(random.x - x, 2) +
		pow(random.y - y, 2));
	nx = (random.x - x) / distance;
	ny = (random.y - y) / distance;
	x += nx * vx * dt;
	y += ny * vy * dt;;
	if (sqrt(pow(x - random.x, 2) + pow(y - random.y, 2)) >= distance)
	{
		vx = 0.085;
		vy = 0.085;
		chaseTime = PHANTOM_BAT_CHASE_TIME;

		isFlyToSimonPos = true;
		isFlyToRandomPos = true;
		x = random.x;
		y = random.y;

	}
	this->SetPosition(x, y);
	SetState(PHANTOM_BAT_STATE_FLYING);
}