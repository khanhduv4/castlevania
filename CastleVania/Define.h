﻿#ifndef _DEFINE_H__
#define _DEFINE_H__

#define SCREEN_WIDTH 528
#define SCREEN_HEIGHT 480

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
#define SIMON_ANI_DIE	25
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

#pragma region SIMON PROPs

#define SIMON_DEFAULT_HEALTH 16
#define SIMON_DEFAULT_HEART 5
#define SIMON_DEFAULT_LIFE 3
#define SIMON_DEFAULT_SUBWEAPON -1

#define SIMON_WALKING_SPEED	0.12f 
#define SIMON_CLIMBING_SPEED 0.09f 

#define SIMON_JUMP_SPEED_Y	0.27f
#define SIMON_VJUMP_HURTING 0.15f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY	0.0007f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_BBOX_WIDTH  32
#define SIMON_BBOX_HEIGHT 59
#define SIMON_BBOX_SITTING_WIDTH 64
#define SIMON_BBOX_SITTING_HEIGHT 45
#define SIMON_BBOX_JUMPING_HEIGHT 45

#define SIMON_UNTOUCHABLE_TIME 2000
#define SIMON_HURTING_TIME 400
#define SIMON_FREEZE_TIME 400

#define SIMON_ATTACK_MAIN_WEAPON	0
#define SIMON_ATTACK_SUB_WEAPON	1

#pragma endregion

#pragma region WEAPON ANI SET ID
#define WEAPON_ANI_SET_SWORD	8
#define WEAPON_ANI_SET_BOOMERANG	14
#define WEAPON_ANI_SET_AXE	12
#define WEAPON_ANI_SET_BLUE	15

#pragma endregion

#pragma region SUBWEAPON ID
#define WEAPON_SWORD 0
#define WEAPON_AXE 1
#define WEAPON_BOOMERANG 2
#define WEAPON_BLUE 3
#pragma endregion

#pragma region ITEM ID

#define ITEM_ID_UPGRADEMORNINGSTAR 1
#define ITEM_ID_LARGEHEART 2
#define ITEM_ID_SWORD 3
#define ITEM_ID_BOOMERANG 4
#define ITEM_ID_II 5
#define ITEM_ID_BLUE 6
#define ITEM_ID_CHICKEN 7
#define ITEM_ID_AXE 8
#define ITEM_ID_SMALLHEART 9
#define ITEM_ID_BOSSITEM	10

#pragma endregion

#pragma region PLAY SCENCE

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_CONFIG 1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_TILEMAP 7 
#define SCENE_SECION_GRID 8

#define OBJECT_TYPE_SIMON	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_TORCH	2
#define OBJECT_TYPE_ENEMY_KNIGHT	3
#define OBJECT_TYPE_ENEMY_BAT	4
#define OBJECT_TYPE_ENEMY_HUNCH_BACK	9
#define OBJECT_TYPE_ENEMY_SKELETON	10
#define OBJECT_TYPE_ENEMY_GHOST	11
#define OBJECT_TYPE_ENEMY_RAVEN	12
#define OBJECT_TYPE_ENEMY_ZOMBIE	13
#define OBJECT_TYPE_ENEMY_PHANTOMBAT	14

#define OBJECT_TYPE_CANDLE	5
#define OBJECT_TYPE_ELEVATOR 6
#define OBJECT_TYPE_STAIR_BEGIN 7
#define OBJECT_TYPE_STAIR_END 8
#define HIDDEN_OBJECT	999


#define OBJECT_TYPE_PORTAL 99

#define MAX_SCENE_LINE 1024
#pragma endregion

#pragma region ENEMY Props
//Ghost
#define GHOST_HP 2
#define GHOST_DAMAGE 1
#define GHOST_DISTANCE_ATTACK_X 100
#define GHOST_DISTANCE_WAITING_X 30

#define GHOST_STATE_DIE 0
#define GHOST_STATE_HIDE 1
#define GHOST_STATE_FLYING 2
#define GHOST_STATE_WAITTING 3

#define GHOST_BBOX_WIDTH 28
#define GHOST_BBOX_HEIGHT 28

#define GHOST_ANI_FLYING_LEFT 0
#define GHOST_ANI_FLYING_RIGHT 1

#define GHOST_FLYING_SPEED_X 0.04

//Raven
#define RAVEN_DISTANCE_X 30
#define RAVEN_DISTANCE_ATTACK_X 80
#define RAVEN_DISTANCE_WAITING_X 60

#define RAVEN_ANI_IDLE_LEFT 0
#define RAVEN_ANI_IDLE_RIGHT 1
#define RAVEN_ANI_FLY_LEFT 2
#define RAVEN_ANI_FLY_RIGHT 3

#define RAVEN_STATE_DIE 0
#define RAVEN_STATE_IDLE 1
#define RAVEN_STATE_FLY 2
#define RAVEN_STATE_WAIT 3
#define RAVEN_STATE_ATTACK 4

#define RAVEN_FLYING_SPEED_X 0.05f
#define RAVEN_FLYING_SPEED_Y 0.05f

//Zoombie
//Zoombie
#define ZOOMBIE_DISTANCE_ATTACK_X 100

#define ZOOMBIE_ANI_WALKING_LEFT 0
#define ZOOMBIE_ANI_WALKING_RIGHT 1
#define ZOOMBIE_ANI_IDLE_LEFT 2
#define ZOOMBIE_ANI_IDLE_RIGHT 3

#define ZOOMBIE_STATE_HIDE    0
#define ZOOMBIE_STATE_WALKING 1
#define ZOOMBIE_STATE_DEAD    2
#define ZOOMBIE_STATE_IDLE    3

#define ZOOMBIE_WALKING_SPEED 0.1f

#define ZOOMBIE_BBOX_WIDTH 34
#define ZOOMBIE_BBOX_HEIGHT 64

//Phantom bat
#define PHANTOM_BAT_HP 16
#define PHANTOM_BAT_DAMAGE 2
#define PHANTOM_BAT_WIDTH 96
#define PHANTOM_BAT_HEIGHT 46

#define PHANTOM_BAT_FLYING_SPEED_X 0.05f
#define PHANTOM_BAT_FLYING_SPEED_Y 0.05f

#define PHANTOM_BAT_STATE_IDLE 0
#define PHANTOM_BAT_STATE_FLYING  1
#define PHANTOM_BAT_STATE_HURT 2

#define PHANTOM_BAT_ANI_IDLE 0
#define PHANTOM_BAT_ANI_FLYING 1

#define PHANTOM_BAT_HURT_TIME	10
#define PHANTOM_BAT_WAIT_TIME	750
#define PHANTOM_BAT_CHASE_TIME	50
#pragma endregion

#endif 