#include "Raven.h"
#include "Define.h"
#include "Simon.h"

Raven::Raven()
{
	this->damage = 1;
	isEnable = true;
	isGravity = 0;
	delayTime = 200;
	SetState(RAVEN_STATE_IDLE);
}

Raven::~Raven()
{

}

void Raven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt, coObjects);
	float simonX, simonY;
	CSimon::GetInstance()->GetPosition(simonX, simonY);
	CSimon* simon = CSimon::GetInstance();
	if (!isEnable && simon->x - startX < 200) {
		isEnable = true;
	}
	if (!isEnable) return;

	if (delayTime > 0) delayTime -= dt;
	else if (delayTime <= 0 && !isChasing) {
		isChasing = true;
		chaseTime = (rand()) % 700 + 500;
		makeRandomLine();
		if (x < simon->x) {
			vx = .05f;
		}
		else vx = -.05f;
	}
	if (y <= 100 || y >= SCREEN_HEIGHT - 100) {
		vy = -vy;
	}
	if (x > 1400) {
		vx = -vx;
	}
	if (isChasing) {
		chaseTime -= dt;
		x += dt * vx;
		y = calculateYLine(x - startX);
		DebugOut(L"X Bat = %f Y Bat  = %f", x - startX, y);
		if (chaseTime <= 0) {
			isChasing = false;
			delayTime = (rand()) % 500 + 500;
		}

	}

}

void Raven::makeLineLeftDown(float simonX) {
	int xA =  -(100);
	int yA = (y + 50 + rand() % 50);
	int xB = x - startX;
	int yB = y;
	aLine = float(yA - yB) / (xA - xB);
	bLine = yA - aLine * xA;
}
void Raven::makeLineRightDown(float simonX) {
	int xA = (100);
	int yA = (y + 50 + rand() % 50);
	int xB = x - startX;
	int yB = y;
	aLine = float(yA - yB) / (xA - xB);
	bLine = yA - aLine * xA;
}

void Raven::makeRandomLine() {
	int screenWidth = SCREEN_WIDTH;
	int screenHeight = SCREEN_HEIGHT;
	float simonX, simonY;
	CSimon::GetInstance()->GetPosition(simonX, simonY);
	simonY -= 50;
	int xA = x > simonX? (100):-100;
	int yA = y > simonY ? (y + 10 + rand() % 30) : -(y + 10 + rand() % 30);
	int xB = x - startX;
	int yB = y;
	aLine = float(yA - yB) / (xA - xB);
	bLine = yA - aLine * xA;
	//Diem A : Vi tri hien tai cua Bat, Diem B: Vi tri dinh cua parabol ^ B.x = random ^ (B.x>0 ^ !bat.isLeft or B.x < 0 ^ bat.isLeft) 
	//Nghiem : Parabol aX^2 + bx + c phai di qua A va B.
	
}
int Raven::calculateYLine(int x) {
	int y = (aLine * x + bLine);
	return y;
}

void Raven::Render()
{
	if (isEnable) {
		int ani = 0;
		switch (state)
		{
		case RAVEN_STATE_IDLE:
		{
			if (nx > 0) {
				ani = RAVEN_ANI_IDLE_RIGHT;
			}
			else {
				ani = RAVEN_ANI_IDLE_LEFT;
			}
			break;
		}
		case RAVEN_STATE_FLY:
		case RAVEN_STATE_WAIT:
		case RAVEN_STATE_ATTACK:
		{
			if (nx > 0) {
				ani = RAVEN_ANI_FLY_RIGHT;
			}
			else {
				ani = RAVEN_ANI_FLY_LEFT;
			}
			break;
		}
		default:
			break;
		}
		animation_set->at(ani)->Render(x, y);

		RenderBoundingBox();
	}

	CEnemy::Render();
}

void Raven::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isFinish) {
		left = 0;
		top = 0;
		right = left + 0;
		bottom = top + 0;
	}
	else {
		left = x;
		top = y;
		right = left + RAVEN_WIDTH;
		bottom = top + RAVEN_HEIGHT;
	}
}

void Raven::SetState(int state)
{
	CEnemy::SetState(state);
	//switch (state)
	//{
	//case RAVEN_STATE_DIE:
	//	//isDeadth = true;
	//	isEnable = false;
	//	break;
	//case RAVEN_STATE_IDLE:
	//	break;
	//case RAVEN_STATE_FLY:
	//	if (nx > 0) {
	//		vx = RAVEN_FLYING_SPEED_X;
	//	}
	//	else {
	//		vx = -RAVEN_FLYING_SPEED_X;
	//	}

	//	if (ny > 0) {
	//		vy = RAVEN_FLYING_SPEED_Y;
	//	}
	//	else {
	//		vy = -RAVEN_FLYING_SPEED_Y;
	//	}

	//	break;
	//case RAVEN_STATE_WAIT:
	//	timeWait = GetTickCount();
	//	vx = 0;
	//	vy = 0;
	//	break;
	//}
}
