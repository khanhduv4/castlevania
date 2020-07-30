#include <time.h>
#include "Define.h"

#include "PhantomBat.h"
#include "Simon.h"

PhantomBat::PhantomBat()
{

	this->Health = 16;
	this->damage = 2;


	srand(time(0));

	delayTime = (rand()) % 500 + 500;
	chaseTime = (rand()) % 500 + 500;
	//bossDeadEffect = new BossDeadEffect(1);
	isFlyToRandomPos = true;
	isFlyToSimonPos = true;

	waitTime = 0;
	hurtTime = PHANTOM_BAT_HURT_TIME;
	isHurted = false;
	isGravity = 0;
	introTime = 2000;
	simonPos.x = -1;
	distance = -1;
	isFinish = 0;


	SetState(PHANTOM_BAT_STATE_IDLE);
}

PhantomBat::~PhantomBat()
{

}
void PhantomBat::makeRandomCurve() {
	int screenWidth = SCREEN_WIDTH;
	int screenHeight = SCREEN_HEIGHT;
	float simonX, simonY;
	CSimon::getInstance()->GetPosition(simonX, simonY);
	
	//Diem A : Vi tri hien tai cua Bat, Diem B: Vi tri dinh cua parabol ^ B.x = random ^ (B.x>0 ^ !bat.isLeft or B.x < 0 ^ bat.isLeft) 
	//Nghiem : Parabol aX^2 + bx + c phai di qua A va B.
	int xB = x < simonX ? (rand() % int((screenHeight-y)/3) + 20) :-(rand() % int((screenHeight - y) / 3) + 20);
	int yB = y - rand() % (int((screenHeight - y) / 3)+20);
	int xA = x-refX;
	int yA =y;
	float a = float(yA-yB) / ((xA * xA - xB * xB) - 2 * (xA - xB) * xB);
	float b = -2 * a * xB;
	float c = yA - a * xA * xA - b * xA;
	aCurve = a;
	bCurve = b;
	cCurve = c;
	int yTest = aCurve * xA * xA + bCurve * xA + cCurve;
	int yTest2 = aCurve * xB * xB + bCurve * xB + cCurve;
}
int PhantomBat::calculateYCurve(int x) {
	return  (aCurve * x * x + bCurve * x + cCurve);
}
void PhantomBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float simonX, simonY;
	CSimon::getInstance()->GetPosition(simonX, simonY);
	CSimon* simon = CSimon::getInstance();
	if (x - simon->x < 100)
		isTest = true;
	if (!isTest) return;
	if (delayTime > 0) delayTime -= dt;
	else if (delayTime <= 0 && !isChasing) {
		if (refX == -1 && refY == -1) {
			refX = simon->x;
			refY = simon->y;
		}
		isChasing = true;
		chaseTime = (rand()) % 2500 + 500;
		makeRandomCurve();
		if (x < simon->x) {
			vx = .01f;
		}
		else vx = -.01f;
	}
	if (isChasing) {
		chaseTime -= dt;
		x += dt * vx;
		y = calculateYCurve(x - refX);
		DebugOut(L"X Bat = %f Y Bat  = %f",x-refX, y);
		if (chaseTime <= 0) {
			isChasing = false;
			delayTime = (rand()) % 500 + 500;
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
		RenderBoundingBox();
	}
	//collisionEffect->Render();

	CEnemy::Render();

}

void PhantomBat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isFinish) {
		left = 0;
		top = 0;
		right = left + 0;
		bottom = top + 0;
	}
	else {
		if (state == PHANTOM_BAT_STATE_FLYING) {
			left = x;
			top = y;

			right = left + 24;
			bottom = top + 21;

		}
		else {
			left = 0;
			top = 0;
			right = left + 0;
			bottom = top + 0;
		}
	}
}

void PhantomBat::SetState(int state)
{
	CEnemy::SetState(state);
}

void PhantomBat::CalculateSimonPos(DWORD dt)
{
	float simonX, simonY;

	CSimon::getInstance()->GetPosition(simonX, simonY);

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
	if (previousHP != Health)
	{
		if (Health <= 0)
		{

			isEnable = false;
			//isDeadth = true;
			//bossDeadEffect->Enable();
			return;
		}
		else
		{
			isHurted = true;
			previousHP = Health;
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
