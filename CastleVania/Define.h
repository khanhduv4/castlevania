#ifndef _DEFINE_H__
#define _DEFINE_H__


#include <fstream> 
#include <string>
#include <stdio.h>
#include <Windows.h>  
#include <iostream>
#include <map>
#include <algorithm>
#include <d3dx9.h>
#include <stdlib.h>
#include <iomanip>
#include <d3d9.h>
#include <vector>
#include <iostream>



using namespace std;


#define COLOR_BLACK D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)  
#define COLOR_KEY D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f) 


#define SCREEN_WIDTH 528
#define SCREEN_HEIGHT 480 


#define IS_DEBUG_RENDER_BBOX isDebug_RenderBBox

#define MAX_FRAME_RATE 90

#define COLOR_BACKGROUND_DEFAULT D3DCOLOR_XRGB(0, 0, 0) // Màu đen

#define TIME_LIMIT_WAIT_RESET_GAME 300 // Thời gian chờ vẽ màn màu đen khi reset game

extern D3DCOLOR D3DCOLOR_BACKGROUND; // màu nền game

#pragma region SIMON ANI ID
#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1

#define SIMON_ANI_WALKING_RIGHT			2
#define SIMON_ANI_WALKING_LEFT			3

#define SIMON_ANI_JUMPING_LEFT	4
#define SIMON_ANI_JUMPING_RIGHT 5

#define SIMON_ANI_ATTACKING_LEFT	6
#define SIMON_ANI_ATTACKING_RIGHT	7

#define SIMON_ANI_SITTING_LEFT	8
#define SIMON_ANI_SITTING_RIGHT 9
#define SIMON_ANI_SITTING_ATTACK_LEFT	10
#define SIMON_ANI_SITTING_ATTACK_RIGHT	11

#define SIMON_ANI_STAIR_CLIMB_UP_RIGHT	12
#define SIMON_ANI_STAIR_CLIMB_UP_LEFT	14
#define SIMON_ANI_STAIR_IDLE_UP_RIGHT	13
#define SIMON_ANI_STAIR_IDLE_UP_LEFT	15
#define SIMON_ANI_STAIR_CLIMB_DOWN_RIGHT	16
#define SIMON_ANI_STAIR_CLIMB_DOWN_LEFT	18
#define SIMON_ANI_STAIR_IDLE_DOWN_RIGHT	17
#define SIMON_ANI_STAIR_IDLE_DOWN_LEFT	19
#define SIMON_ANI_STAIR_UP_ATTACK_RIGHT	20
#define SIMON_ANI_STAIR_UP_ATTACK_LEFT	21
#define SIMON_ANI_STAIR_DOWN_ATTACK_RIGHT	22
#define SIMON_ANI_STAIR_DOWN_ATTACK_LEFT	23

#define SIMON_ANI_HURTING 24
#define SIMON_ANI_DIE	99
#pragma endregion

#pragma region SIMON STATE ID

#define SIMON_STATE_IDLE	0
#define SIMON_STATE_WALKING	1
#define SIMON_STATE_JUMPING	2
#define SIMON_STATE_ATTACKING	3
#define SIMON_STATE_JUMPING_ATTACK	4
#define SIMON_STATE_SITTING	5
#define SIMON_STATE_ON_STAIR	6
#define SIMON_STATE_CLIMBING_UP	7
#define SIMON_STATE_CLIMBING_DOWN	8
#define SIMON_STATE_HURTING	9
#define SIMON_STATE_DIE	9

#pragma endregion

#pragma region SIMON PROP

#define SIMON_WALKING_SPEED	0.12f 
#define SIMON_CLIMBING_SPEED 0.09f 

//0.1f
#define SIMON_JUMP_SPEED_Y	0.27f
#define SIMON_VJUMP_HURTING 0.15f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY	0.0007f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_BBOX_WIDTH  32
#define SIMON_BBOX_HEIGHT 59
#define SIMON_BBOX_SITTING_HEIGHT 45
#define SIMON_BBOX_JUMPING_HEIGHT 45

#define SIMON_UNTOUCHABLE_TIME 2000
#define SIMON_HURTING_TIME 400

#pragma endregion

typedef D3DXVECTOR3 GVector3;
typedef D3DXVECTOR2 GVector2;
#define VECTOR2ZERO GVector2(0.0f, 0.0f)

#define GAMEOVER_SELECT_CONTINUE 0
#define GAMEOVER_SELECT_END 1

#ifndef CHECK_OBJECT_IN_CAMERA // Kiểm tra GameObject có nằm trong camera ko?
#define CHECK_OBJECT_IN_CAMERA(obj) \
checkObjectInCamera(obj->GetX(), obj->GetY(), (float)obj->GetWidth(),  (float)obj->GetHeight())
#endif


#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif

#endif 