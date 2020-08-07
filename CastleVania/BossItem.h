#pragma once


#include "Item.h" 

#define BOSSITEM_GRAVITY 0.25f
#define BOSSITEM_TIMEDISPLAYMAX 3000
#define BOSSITEM_TIMEWAITMAX 300

class BossItem :
	public CItem
{
public:
	BossItem(float X =0, float Y=0);
	 

	~BossItem();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};