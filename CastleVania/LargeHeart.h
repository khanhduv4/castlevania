#ifndef __LARGEHEART_H__
#define __LARGEHEART_H__


#include "Item.h" 

#define LARGEHEART_GRAVITY 0.25f
#define LARGEHEART_TIMEDISPLAYMAX 3000
#define LARGEHEART_TIMEWAITMAX 300

class LargeHeart :
	public CItem
{
public:
	LargeHeart(float X =0, float Y=0);
	 

	~LargeHeart();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};




#endif 

