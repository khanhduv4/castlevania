#ifndef __SMALLHEART_H__
#define __SMALLHEART_H__


#include "Item.h" 

#define LARGEHEART_GRAVITY 0.25f
#define LARGEHEART_TIMEDISPLAYMAX 3000
#define LARGEHEART_TIMEWAITMAX 300

#define SMALLHEART_GRAVITY 0.04f
#define SMALLHEART_TIMEDISPLAYMAX 6000
#define SMALLHEART_TIMEWAITMAX 150

#define SMALLHEART_SPEED_X 0.05f

#define DeltaX 25 //px

class SmallHeart :
	public CItem
{
public:

	SmallHeart(float X =0, float Y=0);
	 
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* listObject = NULL);

	~SmallHeart();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};




#endif 

