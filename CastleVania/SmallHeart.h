#ifndef __SMALLHEART_H__
#define __SMALLHEART_H__


#include "Item.h" 

#define LARGEHEART_GRAVITY 0.25f
#define LARGEHEART_TIMEDISPLAYMAX 3000
#define LARGEHEART_TIMEWAITMAX 300

class SmallHeart :
	public CItem
{
public:
	SmallHeart(float X =0, float Y=0);
	 

	~SmallHeart();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};




#endif 

