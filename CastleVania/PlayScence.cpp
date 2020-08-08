#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include"Tilemap.h"
#include "Torch.h"
#include "Sword.h"
#include "UpgradeMorningStar.h"
#include "LargeHeart.h"
#include "Axe.h"
#include "Boomerang.h"
#include "II.h"
#include "Chicken.h"
#include "Money.h"
#include "Blue.h"
#include "GameBoard.h"
#include "CBurningEffect.h"
#include "Knight.h"
#include "Bat.h"
#include "HunchBack.h"
#include "Skeleton.h"
#include "Ghost.h"
#include "Raven.h"
#include "Zombie.h"
#include "PhantomBat.h"
#include "Candle.h"
#include "Elevator.h"
#include "HiddenObject.h"


using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
	stage = 0;
}

void CPlayScene::_ParseSection_CONFIG(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return; // skip invalid lines

	stage = atoi(tokens[0].c_str());
	time = atoi(tokens[1].c_str());

}

void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}
void CPlayScene::_ParseSection_TILEMAP(string line) {
	vector<string> tokens = split(line);
	if (tokens.size() != 2)
		return;
	TiledMap::Initialize(tokens[0], tokens[1]);
	DebugOut(L"Loaded map");
}
void CPlayScene::_ParseSection_GRID(string line) {
	vector<string> tokens = split(line);
	if (tokens.size() != 3)
		return;
	_grid = Grid::Create(atoi(tokens[0].c_str()), atoi(tokens[1].c_str()), atoi(tokens[2].c_str()), &objects);
	DebugOut(L"Loaded map");
}
void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}
void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}
void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_SIMON:
		obj = CSimon::GetInstance(x, y);
		player = (CSimon*)obj;
		player->getMorningStar()->ResetAniSet();
		break;
	case OBJECT_TYPE_BRICK: obj = new CBrick();
		dynamic_cast<CBrick*>(obj)->SetSize(atoi(tokens[4].c_str()), atoi(tokens[5].c_str()));
		break;
	case OBJECT_TYPE_TORCH: obj = new CTorch(); break;
	case OBJECT_TYPE_ENEMY_KNIGHT: obj = new Knight(atoi(tokens[5].c_str()), atoi(tokens[6].c_str())); break;
	case OBJECT_TYPE_ENEMY_HUNCH_BACK: obj = new Hunchback(); break;
	case OBJECT_TYPE_ENEMY_BAT: obj = new Bat(); break;
	case OBJECT_TYPE_ENEMY_SKELETON: obj = new Skeleton(); break;
	case OBJECT_TYPE_ENEMY_GHOST: obj = new Ghost(); break;
	case OBJECT_TYPE_ENEMY_RAVEN: obj = new Raven(); break;
	case OBJECT_TYPE_ENEMY_ZOMBIE: obj = new Zombie(atoi(tokens[7].c_str())); break;
	case OBJECT_TYPE_ENEMY_PHANTOMBAT: obj = new PhantomBat(); break;
	case OBJECT_TYPE_CANDLE: obj = new Candle(); break;
	case OBJECT_TYPE_ELEVATOR: obj = new Elevator();
		dynamic_cast<Elevator*>(obj)->SetSize(atoi(tokens[4].c_str()), atoi(tokens[5].c_str()));
		break;
	case HIDDEN_OBJECT:
		obj = new HiddenObject(atoi(tokens[6].c_str()));
		if (atoi(tokens[6].c_str())) {
			dynamic_cast<HiddenObject*>(obj)->simonX = atoi(tokens[8].c_str());
			dynamic_cast<HiddenObject*>(obj)->direction = atoi(tokens[9].c_str());
		}
		dynamic_cast<HiddenObject*>(obj)->SetSize(atoi(tokens[4].c_str()), atoi(tokens[5].c_str()));

		break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	if (dynamic_cast<CEnemy*>(obj)) 
		obj->itemId = atoi(tokens[4].c_str());
	obj->SetPosition(x, y);
	if (ani_set_id != -1) {
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
	}

	obj->SetObjId(objects.size());
	if (dynamic_cast<CSimon*>(obj)) {
		player->SetResetPosition(atof(tokens[4].c_str()), atof(tokens[5].c_str()));
		return;
	}
	objects.push_back(obj);
}
void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[CONFIG]") {
			section = SCENE_SECTION_CONFIG;
			continue;
		}
		if (line == "[TEXTURES]") {
			section = SCENE_SECTION_TEXTURES;
			continue;
		}
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[TILEMAP]") {
			section = SCENE_SECTION_TILEMAP; continue;
		}
		if (line == "[GRID]") {
			section = SCENE_SECION_GRID; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_CONFIG: _ParseSection_CONFIG(line); break;
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_TILEMAP: _ParseSection_TILEMAP(line); break;
		case SCENE_SECION_GRID:  _ParseSection_GRID(line); break;
		}
	}

	isReloading = false;

	f.close();

	if (player != NULL) {
		player->setSceneSwitching(false);
	}


	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"Resources\\textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	//Load UI
	CGameBoard::GetInstance()->Load();
	CGameBoard::GetInstance()->ReloadSubWeaponSprites();

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}
void CPlayScene::Update(DWORD dt)
{
	time -= dt;
	if (time <= 0)
	{
		time = 0;
		player->StartOver();
	}
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	//Refactor Item list 
	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> gridObjects;
	coObjects.clear();
	gridObjects.clear();



	if (_grid != NULL) {
		_grid->GetListOfObjects(&coObjects, SCREEN_WIDTH, SCREEN_HEIGHT);
		_grid->GetListOfObjects(&gridObjects, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
	if (isCamLocked) {

		CBrick* leftBound = new CBrick();
		float camX, camY;
		CGame::GetInstance()->GetCamPos(camX, camY);

		leftBound->SetPosition(camX, 0);
		leftBound->SetSize(10, SCREEN_HEIGHT);

		coObjects.push_back(leftBound);
		gridObjects.push_back(leftBound);
	}
	//	DebugOut(L"Size of objects = %d", coObjects.size());
		/*for (size_t i = 1; i < objects.size(); i++)
		{
			coObjects.push_back(objects[i]);
		}*/
	player->Update(dt, &coObjects, &items);
	if (this->player->IsInNewScene())
		return;
	if (_grid == NULL)
		return;
	for (size_t i = 0; i < gridObjects.size(); i++)
	{
		if (dynamic_cast<PhantomBat*>(gridObjects[i]))
			isBossScene = true;
		if (dynamic_cast<CSimon*>(gridObjects[i])) continue;
		if (dynamic_cast<Weapon*> (gridObjects[i])) { (dynamic_cast<Weapon*> (gridObjects[i]))->Update(dt, &coObjects, &items); }
		else {
			gridObjects[i]->Update(dt, &coObjects);
		}
	}
	for (int i = 0; i < items.size(); i++) {
		if (!items[i]->isFinish || !dynamic_cast<CBurningEffect*>(items[i]))
			items[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario

	CGame* game = CGame::GetInstance();
	float camX, camY;
	game->GetCamPos(camX, camY);
	float cx, cy;
	player->GetPosition(cx, cy);
	if ((isBossScene && cx >= (TiledMap::GetCurrentMap()->GetWidth() - SCREEN_WIDTH / 2)))
		isCamLocked = true;
	if ((isBossScene && cx < (TiledMap::GetCurrentMap()->GetWidth() - SCREEN_WIDTH - 50)))
		isCamLocked = false;
	if (!isCamLocked) {


		float mapWidth = TiledMap::GetCurrentMap()->GetWidth();

		if (cx > game->GetScreenWidth() / 2)
			cx -= game->GetScreenWidth() / 2;
		else cx = 0;
		if (cx + game->GetScreenWidth() >= mapWidth - 15)
			cx = mapWidth - 15 - game->GetScreenWidth();

		cy -= game->GetScreenHeight() / 2;
		game->SetCamPos(cx, 0.f);
	}


	// Update ScoreBoard

	CGameBoard::GetInstance()->Update(dt,time, stage);

	_grid->UpdateGrid();
}

void CPlayScene::Render()
{

	TiledMap::GetCurrentMap()->Render();

	vector<LPGAMEOBJECT> gridObjects;
	vector<LPGAMEOBJECT> enemyObjs;
	gridObjects.clear();
	enemyObjs.clear();
	if (_grid)
		_grid->GetListOfObjects(&gridObjects, SCREEN_WIDTH, SCREEN_HEIGHT);
	//Render game Object 
	for (int i = 0; i < gridObjects.size(); i++) {
		if (gridObjects[i]->isFinish && !gridObjects[i]->objLife)
			continue;
		if (dynamic_cast<CEnemy*>(gridObjects[i]))
		{
			if (dynamic_cast<CEnemy*>(gridObjects[i])->isFront)
			{
				enemyObjs.push_back(gridObjects[i]);
				continue;
			}
		}
		gridObjects[i]->Render();
	}
	for (int i = 0; i < enemyObjs.size(); i++) {
		enemyObjs[i]->Render();
	}
	player->Render();
	// Render Items
	for (int i = 0; i < items.size(); i++) {
		items[i]->Render();
	}

	CGameBoard::GetInstance()->Render();

}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	isReloading = true;
	for (int i = 0; i < objects.size(); i++) {

		delete objects[i];
	}

	for (int i = 0; i < items.size(); i++)
		delete items[i];
	delete _grid;
	objects.clear();
	items.clear();
	//player = NULL;
	_grid = NULL;
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{

	CGame* game = CGame::GetInstance();

	CSimon* simon = ((CPlayScene*)scence)->GetPlayer();
	if (simon->IsAttacking()) return;
	if (simon->isHurting) return;

	switch (KeyCode)
	{
	case DIK_SPACE:
		if (simon->IsSitting() || simon->isStair) return;
		simon->SetState(SIMON_STATE_JUMPING);
		break;
	case DIK_Q:
		simon->setHealth(16);
		break;

	case DIK_P:
		simon->SetHurt(new CCollisionEvent(0.2, 0.2, 0.2));
		break;
	case DIK_RETURN:
		CGameBoard::GetInstance()->Start();
		break;
	case DIK_S:
		if (game->IsKeyDown(DIK_UP)) {
			if (simon->getCurrentSubWeapon() != -1 && simon->getHeart() > 0) {
				simon->setWeapon(SIMON_ATTACK_SUB_WEAPON);
				simon->SetState(SIMON_STATE_ATTACKING);
			}
		}
		else {
			simon->setWeapon(SIMON_ATTACK_MAIN_WEAPON);
			simon->SetState(SIMON_STATE_ATTACKING);
		}

		break;


	case DIK_A:
		simon->Reset();
		break;


	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode) {
	CSimon* simon = ((CPlayScene*)scence)->GetPlayer();
	if (KeyCode == DIK_DOWN) {
		if (!simon->isStair)
			simon->SetSitting(0);
	}
	else if (KeyCode == DIK_UP) {
		simon->isClimbing = 0;
	}
}
void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CSimon* simon = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when SIMON
	if (simon->GetState() == SIMON_STATE_DIE) return;
	if (simon->IsAttacking()) return;


	if (!CGameBoard::GetInstance()->IsStarted()) return;
	if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT)) {
		if (simon->IsAttacking() || simon->isStair || simon->isHurting) return;
		simon->SetState(SIMON_STATE_WALKING);
		if (game->IsKeyDown(DIK_RIGHT)) simon->setDirection(1);
		else simon->setDirection(-1);
	}
	else if (game->IsKeyDown(DIK_DOWN) && !simon->IsJumping())
	{
		if (simon->isClimbableDown) {
			simon->SetState(SIMON_STATE_CLIMBING_DOWN);
			return;
		}
		else if (simon->IsJumping()) return;
		simon->SetState(SIMON_STATE_SITTING);
	}
	else if (game->IsKeyDown(DIK_UP) && !simon->IsJumping()) {
		if (simon->isClimbableUp)
			simon->SetState(SIMON_STATE_CLIMBING_UP);
	}
	else {
		if (simon->isStair) simon->SetState(SIMON_STATE_ON_STAIR);
		else simon->SetState(SIMON_STATE_IDLE);
	}
}